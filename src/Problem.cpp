#include "Problem.hpp"

#include <iostream>

Problem1::Problem1(SchedSpec& specs) : _specs(specs) {
    std::cout << A(1, 1) << std::endl;
    std::cout << A(1, 2) << std::endl;
    std::cout << A(2, 1) << std::endl;
    std::cout << A(2, 2) << std::endl;
}

bool Problem1::A(int e, int x) {
    e--; x--;
    for (int i = 0; i < this->_specs.a->at(e)->size(); ++i) {
        if (this->_specs.a->at(e)->at(i) == x) {
            return true;
        }
    }
    return false;
}

bool Problem1::B(int p, int x) {

}

bool Problem1::C(int s, int i) {

}

bool Problem1::M(int x, int s, int t) {

}

int Problem1::N(int x) {

}
