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

void Problem1::constraint() {
    constraint1();
    constraint2();
    constraint3();
    constraint4();
    constraint5();
    constraint6();
    constraint7();
    constraint8();
    constraint9();
}

void Problem1::constraint1() {

    FOR(t,1,this->_specs.T){
        FOR(x,1,this->_specs.X){
            FOR(s,1, this->_specs.S){
                // this->_solver.addUnit(Lit(this->_props[x][s][t]));
                // this->_solver.addUnit(Lit(this->C(s, N(x))));
            }
        }
    }
}

void Problem1::constraint2() {
    FOR(t, 1, this->_specs.T) {
        FOR(s, 1, this->_specs.S) {
            FOR(e, 1, this->_specs.E) {
                FOR(i, 1, this->_specs.X) {
                    if (this->A(e, i)) {
                        FOR(j, 1, i) {
                            this->_solver.addBinary(~Lit(this->_props[i][s][t]),
                                                    ~Lit(this->_props[j][s][t]));
                        }
                    }
                }
            }
        }
    }
}

void Problem1::constraint3() {
    FOR(t, 1, this->_specs.T) {
        FOR(s, 1, this->_specs.S) {
            FOR(p, 1, this->_specs.P) {
                FOR(i, 1, this->_specs.X) {
                    if (this->B(p, i)) {
                        FOR(j, 1, i) {
                            this->_solver.addBinary(~Lit(this->_props[i][s][t]),
                                                    ~Lit(this->_props[j][s][t]));
                        }
                    }
                }
            }
        }
    }
}

void Problem1::constraint4() {
    vec<Lit> lits;
    FOR(x,1,this->_specs.X){
        lits.clear();
        FOR(p,1, this->_specs.P){
            lits.push(Lit(B(p,x)));
        }
        this->_solver.addClause(lits);
    }
}


void Problem1::constraint5() {
    vec<Lit> lits;
    FOR(x,1,this->_specs.X){
        lits.clear();
        FOR(e,1, this->_specs.E){
            lits.push(Lit(A(e,x)));
        }
        this->_solver.addClause(lits);
    }
}

void Problem1::constraint6() {

    FOR(x,1,this->_specs.X){
        FOR(p,1, this->_specs.P){
            FOR(j,1,p){
                this->_solver.addBinary(~Lit(B(j,x)), ~Lit(B(p,x)));
            }
        }
    }
}

void Problem1::constraint7() {

}

void Problem1::constraint8() {

}

void Problem1::constraint9() {

}

