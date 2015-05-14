#include "Problem5.hpp"

#include <iostream>
#include <cassert>


// void Problem5::test() {
//     Problem4::test();
//     assert(D(1) == 2);
//     assert(D(2) == 4);
//     assert(D(3) == 2);
//     assert(D(4) == 3);
// }

int Problem5::D(int x) {
    x--;
    return this->_specs.d->at(x);
}

void Problem5::setConstraints(){
    Problem4::setConstraints();
    this->_constraints.erase("examen_temps_max");
    this->_constraints["examen_duree"] = [this]() {
        FOR(x1, 1, this->_specs.X) {
            FOR(x2, 1, this->_specs.X) {
                if (x1 != x2) {
                FOR(s, 1, this->_specs.S) {
                    FOR(t1, 1, this->_specs.T) {
                        FOR(t2, 1, this->_specs.T) {
                            if (t1 <= t2 + D(x2)-1 and t1 + D(x1)-1 >= t2) {
                                this->_solver.addBinary(~Lit(this->_props[x1][s][t1]),                    ~Lit(this->_props[x2][s][t2]));
                            }
                        }
                    }
                }
            }
            }
        }
    };
}