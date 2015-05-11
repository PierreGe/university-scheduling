#ifndef __PROBLEM_HPP
#define __PROBLEM_HPP

#include <unordered_map>
#include <functional>
#include <string>

#include "parser/SchedSpec.hpp"
#include "minisat/Solver.hpp"

class Problem1 {
protected:
    SchedSpec _specs;
    Solver _solver;
    int*** _props;
    std::unordered_map<std::string, std::function<void()>> _constraints;
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
    void virtual setConstraints();
public:
    void test();
};

#endif // __PROBLEM_HPP