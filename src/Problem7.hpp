#ifndef __PROBLEM7_HPP
#define __PROBLEM7_HPP

#include <unordered_map>
#include <functional>
#include <string>

#include "parser/SchedSpec.hpp"
#include "minisat/Solver.hpp"

#include "Problem6.hpp"

class Problem7 : public Problem6 {
public:
    using Problem6::Problem6;
protected:
    virtual void setConstraints();
    int NA(int);
    void max_salle(int, vec<Lit>, int, int);
public:
    // virtual void test();
};

#endif // __PROBLEM_HPP