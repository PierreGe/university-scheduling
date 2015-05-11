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
}