#ifndef __PROBLEM6_HPP
#define __PROBLEM6_HPP

#include <unordered_map>
#include <functional>
#include <string>

#include "parser/SchedSpec.hpp"
#include "minisat/Solver.hpp"

#include "Problem5.hpp"

class Problem6 : public Problem5 {
public:
    using Problem5::Problem5;
protected:
    virtual void setConstraints();
    bool J(int t);
public:
    // virtual void test();
};

#endif // __PROBLEM_HPP