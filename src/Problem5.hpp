#ifndef __PROBLEM5_HPP
#define __PROBLEM5_HPP

#include <unordered_map>
#include <functional>
#include <string>

#include "parser/SchedSpec.hpp"
#include "minisat/Solver.hpp"

#include "Problem4.hpp"

class Problem5 : public Problem4 {
public:
    using Problem4::Problem4;
protected:
    virtual void setConstraints();

};

#endif // __PROBLEM_HPP