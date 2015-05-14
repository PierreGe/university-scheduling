#include "Problem6.hpp"

#include <iostream>
#include <cassert>


bool Problem6::J(int t) {
    for (auto period : this->_specs.I) {
        if (t >= period.first and t <= period.second){
            return false;
        }
    }
    return true;
}

void Problem6::setConstraints(){
    Problem5::setConstraints();
    this->_constraints["examen_horaire_nuit"] = [this]() {
        FOR(x, 1, this->_specs.X) {
            FOR(s, 1, this->_specs.S) {
                FOR(t, 1, this->_specs.T) {
                    if (not J(t)) {
                        this->_solver.addUnit(~Lit(this->_props[x][s][t]));
                    }
                }
            }
        }
    };
}