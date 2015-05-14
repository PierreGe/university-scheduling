#include "Problem4.hpp"

#include <iostream>
#include <cassert>
#include <sstream>

void Problem4::test() {
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

Problem4::Problem4(SchedSpec& specs) : _specs(specs), _solver(), _constraints() {
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
}
    
Problem4::~Problem4() {
    for (int i = 1; i <= this->_specs.X; ++i) {
        for (int j = 1; j <= this->_specs.S; ++j) {
            delete[] this->_props[i][j];
        }
        delete[] this->_props[i];
    }
    delete[] this->_props; 
}

void Problem4::solve() {
    this->setConstraints();
    for (auto& i : this->_constraints)
    {
        i.second();
    }
    this->_solver.solve();
}

bool Problem4::okay() {
    return this->_solver.okay();
}

void Problem4::output() {
    if (this->okay()){
        std::stringstream ss;
        ss << std::endl << "OUTPUT : ";
        FOR(x, 1, this->_specs.X) {
            FOR(s, 1, this->_specs.S) {
                FOR(t, 1, this->_specs.T) {
                    if (this->_solver.model[this->_props[x][s][t]] == l_True) {
                        std::cout << "Examen " << x << " dans la salle " << s << " au temps " << t << std::endl;
                        ss << s << "," << t << ";";
                    }
                }
            }
        }
        std::cout << ss.str() << std::endl;
    }
    else{
        std::cout << "\nOUTPUT : 0"<< std::endl;
    }
}

bool Problem4::A(int e, int x) {
    e--;
    for (int i = 0; i < this->_specs.a->at(e)->size(); ++i) {
        if (this->_specs.a->at(e)->at(i) == x) {
            return true;
        }
    }
    return false;
}

bool Problem4::B(int p, int x) {
    p--;
    for (int i = 0; i < this->_specs.b->at(p)->size(); ++i) {
        if (this->_specs.b->at(p)->at(i) == x) {
            return true;
        }
    }
    return false;
}

bool Problem4::C(int s, int i) {
    s--;
    return (this->_specs.c->at(s) >= i);
}

int Problem4::N(int x) {
    int res = 0;
    for (int e = 0; e < this->_specs.E; ++e) {
        res += A(e+1,x);
    }
    return res;
}

void Problem4::setConstraints() {
    // Contrainte d'existence
    _constraints["existence"] = [this]() {
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
    };
    // Le nombre d'étudiant dans une salle ne peut pas dépasser sa capacité
    _constraints["salle_capacite"] = [this]() {
        FOR(t,1,this->_specs.T){
            FOR(x,1,this->_specs.X){
                FOR(s,1, this->_specs.S){
                    if (not this->C(s, N(x))) {
                        this->_solver.addUnit(~Lit(this->_props[x][s][t]));
                    }
                }
            }
        }
    };
    // Un étudiant a au plus un examen à chaque moment
    _constraints["etudiant_temps_max"] = [this]() {
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
    };
    // Un professeur donne au plus un examen à chaque moment
    _constraints["prof_temps_max"] = [this]() {
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
    };
    // Un examen doit avoir au moins un professeur
    _constraints["examen_prof_min"] = [this]() {
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
    };
    // Un examen doit avoir au moins un étudiant
    _constraints["examen_etudiant_min"] = [this]() {
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
    };
    // Chaque examen se déroule à au plus un moment
    _constraints["examen_temps_max"] = [this]() {
        FOR(x, 1, this->_specs.X) {
            FOR(s, 1, this->_specs.S) {
                FOR(t1, 1, this->_specs.T) {
                    FOR(t2, t1 + 1, this->_specs.T) {
                        this->_solver.addBinary(~Lit(this->_props[x][s][t1]), ~Lit(this->_props[x][s][t2]));
                    }
                }
            }
        }
    };

    // Dans une salle, au plus un examen au même moment
    _constraints["salle_examen_max"] = [this]() {
        FOR(s, 1, this->_specs.S) {
            FOR(t, 1, this->_specs.T) {
                FOR(x1, 1, this->_specs.X) {
                    FOR(x2, x1 + 1, this->_specs.X) {
                        this->_solver.addBinary(~Lit(this->_props[x1][s][t]), ~Lit(this->_props[x2][s][t]));
                    }
                }
            }
        }
    };
}

