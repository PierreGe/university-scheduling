#ifndef __PROBLEM8_HPP
#define __PROBLEM8_HPP

#include <unordered_map>
#include <functional>
#include <string>

#include "parser/SchedSpec.hpp"
#include "minisat/Solver.hpp"

#include "Problem7.hpp"

class Problem8 : public Problem6 {
public:
    using Problem6::Problem6;
protected:
    virtual void setConstraints();
public:
    // virtual void test();
};

#endif // __PROBLEM_HPP