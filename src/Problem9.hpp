#ifndef __PROBLEM9_HPP
#define __PROBLEM9_HPP

#include <unordered_map>
#include <functional>
#include <string>

#include "parser/SchedSpec.hpp"
#include "minisat/Solver.hpp"

#include "Problem7.hpp"

class Problem9 : public Problem7 {
public:
    using Problem7::Problem7;
protected:
    virtual void setConstraints();
public:
    // virtual void test();
};

#endif // __PROBLEM_HPP