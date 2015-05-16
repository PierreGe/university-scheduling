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
    std::vector<std::vector<int>> permut_etudiant_salles(int);
    void permut_etudiant_temps(int, int, const std::vector<std::vector<int>>&, std::vector<int>);
public:
    // virtual void test();
};

#endif // __PROBLEM_HPP