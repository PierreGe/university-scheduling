#include "Problem5.hpp"

#include <iostream>
#include <cassert>


void Problem5::setConstraints(){
    Problem4::setConstraints();
    this->_constraints.erase("examen_temps_max");
}