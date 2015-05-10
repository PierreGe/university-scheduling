#include "Problem.hpp"

#include <iostream>
#include <cassert>



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
    this->_props = new int**[this->_specs.X];
    for (int i = 0; i < this->_specs.X; ++i) {
        this->_props[i] = new int*[this->_specs.S];
        for (int j = 0; j < this->_specs.S; ++j) {
            this->_props[i][j] = new int[this->_specs.T];
            for (int k = 0; k < this->_specs.T; ++k) {
                this->_props[i][j][k] = this->_solver.newVar();
            }
        }
    }
}
    
Problem1::~Problem1() {
    for (int i = 0; i < this->_specs.X; ++i) {
        for (int j = 0; j < this->_specs.S; ++j) {
            delete[] this->_props[i][j];
        }
        delete[] this->_props[i];
    }
    delete[] this->_props;
}

void Problem1::solve() {
    this->_solver.solve();
}

bool Problem1::okay() {
    return this->_solver.okay();
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
