#include "Problem.hpp"

#include <iostream>
#include <cassert>

#define FOR(k, lb, ub) for (int k = (lb) ; (k) <= (ub) ; (k)++)

void Problem1::test() {
    assert(A(1, 1));
    assert(A(1, 2));
    assert(A(2, 1));
    assert(A(2, 2) == false);

    assert(B(1, 1));
    assert(B(1, 2) == false);
    assert(B(2, 1) == false);
    assert(B(2, 2));


    assert(N(1) == 2);
    assert(N(2) == 1);
}

Problem1::Problem1(SchedSpec& specs) : _specs(specs), _solver() {
    this->_props = new int**[this->_specs.X +1];
    for (int i = 1; i <= this->_specs.X; ++i) {
        this->_props[i] = new int*[this->_specs.S+1];
        for (int j = 1; j <= this->_specs.S; ++j) {
            this->_props[i][j] = new int[this->_specs.T+1];
            for (int k = 1; k <= this->_specs.T; ++k) {
                this->_props[i][j][k] = this->_solver.newVar();
            }
        }
    }
    constraint();
}
    
Problem1::~Problem1() {
    /*for (int i = 0; i < this->_specs.X; ++i) {
        for (int j = 0; j < this->_specs.S; ++j) {
            delete[] this->_props[i][j];
        }
        delete[] this->_props[i];
    }
    delete[] this->_props; */
}

void Problem1::solve() {
    this->_solver.solve();
}

bool Problem1::okay() {
    return this->_solver.okay();
}

void Problem1::display() {
    FOR(x, 1, this->_specs.X) {
        FOR(s, 1, this->_specs.S) {
            FOR(t, 1, this->_specs.T) {
                // FOR(i, 0, 4096) {
                //     std::cout<< i;
                //     if (this->_solver.model[i] == l_True) {
                //         std::cout << " True" << std::endl;
                //     }
                //     else {
                //         std::cout << " False" << std::endl;
                //     }
                // }
                if (this->_solver.model[this->_props[x][s][t]] == l_True) {
                    std::cout << "Examen " << x << " dans la salle " << s << " au temps " << t << std::endl;
                }
            }
        }
    }
}

bool Problem1::A(int e, int x) {
    e--;
    for (int i = 0; i < this->_specs.a->at(e)->size(); ++i) {
        if (this->_specs.a->at(e)->at(i) == x) {
            return true;
        }
    }
    return false;
}

bool Problem1::B(int p, int x) {
    p--;
    for (int i = 0; i < this->_specs.b->at(p)->size(); ++i) {
        if (this->_specs.b->at(p)->at(i) == x) {
            return true;
        }
    }
    return false;
}

bool Problem1::C(int s, int i) {
    s--;
    return (this->_specs.c->at(s) >= i);
}

int Problem1::N(int x) {
    int res = 0;
    for (int e = 0; e < this->_specs.E; ++e) {
        res += A(e+1,x);
    }
    return res;
}

void Problem1::existenceConstraint() {
    vec<Lit> lits;
    // Contrainte d'existence
    FOR(x, 1, this->_specs.X){
        lits.clear();
        FOR(s, 1, this->_specs.S){
            FOR(t, 1, this->_specs.T){
                lits.push(Lit(this->_props[x][s][t]));
            }
        }
        this->_solver.addClause(lits);
    }
}

void Problem1::constraint() {
    existenceConstraint();
    constraint1();
    constraint2();
    constraint3();
    constraint4();
    constraint5();
    // constraint6(); // Not working but not mandatory
    constraint7();
    constraint8();
    constraint9();
}
// Le nombre d'étudiant dans une salle ne peut pas dépasser sa capacité
void Problem1::constraint1() {
    FOR(t,1,this->_specs.T){
        FOR(x,1,this->_specs.X){
            FOR(s,1, this->_specs.S){
                if (not this->C(s, N(x))) {
                    this->_solver.addUnit(~Lit(this->_props[x][s][t]));
                }
            }
        }
    }
}
// Un étudiant a au plus un examen à chaque moment
void Problem1::constraint2() {
    FOR(e, 1, this->_specs.E) {
        FOR(t, 1, this->_specs.T) {
            FOR(s1, 1, this->_specs.S) {
                FOR(s2, 1, this->_specs.S) {
                    FOR(x1, 1, this->_specs.X) {
                        FOR(x2, x1 + 1, this->_specs.X) {
                            if (A(e, x1) and A(e, x2)) {
                                this->_solver.addBinary(~Lit(this->_props[x1][s1][t]),
                                                        ~Lit(this->_props[x2][s2][t]));
                            }
                        }
                    }
                }
            }
        }
    }
}
// Un professeur donne au plus un examen à chaque moment
void Problem1::constraint3() {
    FOR(p, 1, this->_specs.P) {
        FOR(t, 1, this->_specs.T) {
            FOR(s1, 1, this->_specs.S) {
                FOR(s2, 1, this->_specs.S) {
                    FOR(x1, 1, this->_specs.X) {
                        FOR(x2, x1 + 1, this->_specs.X) {
                            if (B(p, x1) and B(p, x2)) {
                                this->_solver.addBinary(~Lit(this->_props[x1][s1][t]),
                                                        ~Lit(this->_props[x2][s2][t]));
                            }
                        }
                    }
                }
            }
        }
    }
}
// Un examen doit avoir au moins un professeur
void Problem1::constraint4() {
    vec<Lit> lits;
    FOR(x,1,this->_specs.X){
        lits.clear();
        FOR(s,1,this->_specs.S){
            FOR(t,1,this->_specs.T){
                FOR(p,1, this->_specs.P){
                    if (B(p,x)) {
                        lits.push(Lit(this->_props[x][s][t]));
                    }
                }
            }
        }
        this->_solver.addClause(lits);
    }
}

// Un examen doit avoir au moins un étudiant
void Problem1::constraint5() {
    vec<Lit> lits;
    FOR(x,1,this->_specs.X){
        lits.clear();
        FOR(s,1,this->_specs.S){
            FOR(t,1,this->_specs.T){
                FOR(e,1, this->_specs.E){
                    if (A(e,x)) {
                        lits.push(Lit(this->_props[x][s][t]));
                    }
                }
            }
        }
        this->_solver.addClause(lits);
    }
}


// Un examen a au plus un professeur
void Problem1::constraint6() {
    FOR(x, 1, this->_specs.X) {
        vec<Lit> lits;
        FOR(s, 1, this->_specs.S) {
            FOR(t, 1, this->_specs.T) {
                FOR(p1, 1, this->_specs.P) {
                    FOR(p2, p1 + 1, this->_specs.P) {
                        if (not B(p1, x) or not B(p2, x))
                            lits.push(Lit(this->_props[x][s][t]));
                    }
                }
            }
        }
        this->_solver.addClause(lits);
    }
}


// Chaque examen se déroule à au plus un moment
void Problem1::constraint7() {
    FOR(x, 1, this->_specs.X) {
        FOR(s, 1, this->_specs.S) {
            FOR(t1, 1, this->_specs.T) {
                FOR(t2, t1 + 1, this->_specs.T) {
                    this->_solver.addBinary(~Lit(this->_props[x][s][t1]), ~Lit(this->_props[x][s][t2]));
                }
            }
        }
    }
}
// Chaque examen dans au plus une salle
void Problem1::constraint8() {
    FOR(t, 1, this->_specs.T) {
        FOR(x, 1, this->_specs.X) {
            FOR(s1, 1, this->_specs.S) {
                FOR(s2, s1 + 1, this->_specs.S) {
                    this->_solver.addBinary(~Lit(this->_props[x][s1][t]), ~Lit(this->_props[x][s2][t]));
                }
            }
        }
    }
}
// Dans une salle, au plus un examen au même moment
void Problem1::constraint9() {
    FOR(s, 1, this->_specs.S) {
        FOR(t, 1, this->_specs.T) {
            FOR(x1, 1, this->_specs.X) {
                FOR(x2, x1 + 1, this->_specs.X) {
                    this->_solver.addBinary(~Lit(this->_props[x1][s][t]), ~Lit(this->_props[x2][s][t]));
                }
            }
        }
    }
}

