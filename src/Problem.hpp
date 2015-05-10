#ifndef __PROBLEM_HPP
#define __PROBLEM_HPP

#include "parser/SchedSpec.hpp"

class Problem1 {
private:
    SchedSpec _specs;
public:
    Problem1(SchedSpec&);
private:
    bool A(int e, int x);
    bool B(int p, int x);
    bool C(int s, int i);
    int N(int x);
public:
    void test();
};

#endif // __PROBLEM_HPP