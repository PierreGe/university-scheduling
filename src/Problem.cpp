#include "Problem.hpp"

#include <iostream>
#include <cassert>

Problem1::Problem1(SchedSpec& specs) : _specs(specs) {

}

void Problem1::test() {
    assert(A(1, 1));
    assert(A(1, 2));
    assert(A(2, 1));
    assert(A(2, 2) == false);

    assert(B(1, 1));
    assert(B(1, 2) == false);
    assert(B(2, 1) == false);
    assert(B(2, 2));
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

}

int Problem1::N(int x) {

}
