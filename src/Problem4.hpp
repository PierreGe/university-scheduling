#ifndef __PROBLEM4_HPP
#define __PROBLEM4_HPP

#include <unordered_map>
#include <functional>
#include <string>

#include "parser/SchedSpec.hpp"
#include "minisat/Solver.hpp"

#define FOR(k, lb, ub) for (int k = (lb) ; (k) <= (ub) ; (k)++)

class Problem4 {
protected:
    SchedSpec _specs;
    Solver _solver;
    int*** _props;
    std::unordered_map<std::string, std::function<void()>> _constraints;
public:
    Problem4(SchedSpec&);
    ~Problem4();
    void solve();
    bool okay();
    void output();
protected:
    bool A(int e, int x);
    bool B(int p, int x);
    bool C(int s, int i);
    int N(int x);
    virtual 
    void setConstraints();
public:
    void test();
};

#endif // __PROBLEM_HPP