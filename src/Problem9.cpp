#include "Problem9.hpp"

#include <iostream>
#include <cassert>


void Problem9::setConstraints(){
    Problem7::setConstraints();
    // Un étudiant a au plus un examen à chaque moment
    _constraints["etudiant_temps_max"] = [this]() {
        FOR(e, 1, this->_specs.E) {
            FOR(t1, 1, this->_specs.T) {
                FOR(t2, 1, this->_specs.T) {
                    FOR(s1, 1, this->_specs.S) {
                        FOR(s2, 1, this->_specs.S) {
                            if (s1 != s2) {
                                FOR(x1, 1, this->_specs.X) {
                                    FOR(x2, x1 + 1, this->_specs.X) {
                                        if (A(e, x1) and A(e, x2) and t1 <= t2 + D(x2) and t1 + D(x1) >= t2) {
                                            this->_solver.addBinary(~Lit(this->_props[x1][s1][t1]),
                                                                    ~Lit(this->_props[x2][s2][t2]));
                                        }
                                    }
                                }
                            }
                            else{
                                FOR(x1, 1, this->_specs.X) {
                                    FOR(x2, x1 + 1, this->_specs.X) {
                                        if (A(e, x1) and A(e, x2) and t1 <= t2 + D(x2)-1 and t1 + D(x1)-1 >= t2) {
                                            this->_solver.addBinary(~Lit(this->_props[x1][s1][t1]),
                                                                    ~Lit(this->_props[x2][s2][t2]));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    };   
}