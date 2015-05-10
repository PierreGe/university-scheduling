#ifndef __PROBLEM_HPP
#define __PROBLEM_HPP

#include "parser/SchedSpec.hpp"
#include "minisat/Solver.hpp"

class Problem1 {
protected:
    SchedSpec _specs;
    Solver _solver;
    int*** _props;
public:
    Problem1(SchedSpec&);
    ~Problem1();
    void solve();
    bool okay();
    void display();
protected:
    bool A(int e, int x);
    bool B(int p, int x);
    bool C(int s, int i);
    int N(int x);
    void constraint();
    void constraint1();
    void constraint2();
    void constraint3();
    void constraint4();
    void constraint5();
    void constraint6();
    void constraint7();
    void constraint8();
    void constraint9();
public:
    void test();
};

#endif // __PROBLEM_HPP