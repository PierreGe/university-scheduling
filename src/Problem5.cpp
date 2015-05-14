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
        FOR(x, 1, this->_specs.X) {
            FOR(t1, 1, D(x)) {
                vec<Lit> lits;
                for(int t2 = 0; t2 <= this->_specs.T; t2 += D(x)) {
                    if (t1 + t2 <= this->_specs.T) {
                        FOR(s, 1, this->_specs.S) {
                            lits.push(Lit(this->_props[x][s][t1+t2]));
                        }
                    }
                }
                this->_solver.addClause(lits);

            }
        }
    };

    // Chaque examen dans au plus une salle
       _constraints["examen_salle_max"] = [this]() {
               FOR(x, 1, this->_specs.X) {
                   FOR(t1, 1, this->_specs.T) {
                       FOR(t2, 1, this->_specs.T) {
                           FOR(s1, 1, this->_specs.S) {
                               FOR(s2, s1 + 1, this->_specs.S) {
                                   this->_solver.addBinary(~Lit(this->_props[x][s1][t1]), ~Lit(this->_props[x][s2][t2]));
                               }
                           }
                       }
                   }
               }
           };
}