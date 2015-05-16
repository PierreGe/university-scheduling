#include "Problem7.hpp"

#include <iostream>
#include <cassert>


int Problem7::NA(int e) {
    int res = 0;
    FOR(x, 1, this->_specs.X) {
        res += A(e, x);
    }
    return res;
}

void Problem7::max_salle(int e, vec<Lit> lits, int k, int nx) {
    if (k < 0 and nx == 0) {
        this->_solver.addClause(lits);
    }
    else {
        FOR(x1, 1, this->_specs.X) {
            FOR(x2, 1, this->_specs.X) {
                if (A(e, x1) and A(e, x2) and x1 != x2) {
                    FOR(s1, 1, this->_specs.S) {
                        FOR(s2, 1, this->_specs.S) {
                            FOR(t1, 1, this->_specs.T) {
                                FOR(t2, t1 + 1, this->_specs.T) {
                                    lits.push(~Lit(this->_props[x1][s1][t1]));
                                    if (s1 == s2) {
                                        max_salle(e, lits, k, nx-1);
                                    }
                                    else {
                                        max_salle(e, lits, k-1, nx-1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Problem7::setConstraints(){
    Problem6::setConstraints();
    this->_constraints["etudiant_max_salle"] = [this]() {
        FOR(e, 1, this->_specs.E) {
            vec<Lit> lits;
            this->max_salle(e, lits, this->_specs.k, this->NA(e));
        }
    };
}