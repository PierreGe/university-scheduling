#ifndef PROBLEM
#define PROBLEM

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Parser.hpp"
#include "Model.hpp"
#include "Types.hpp"
#include "SolutionInterpreter.hpp"

using namespace std;

#define NOVERTWO 0
#define SQRTOFN 1
#define PAIRWISE 2
#define BINARY 3

class Problem
{
public:
    Problem();
    Problem(Problem* modelerToCopy);
    ~Problem();
    void RunQ1(string in_file_name, string dimacs_file, string out_file_name);
    void RunQ2(string in_file_name, string dimacs_file, string out_file_name);
    void RunQ3(string in_file_name, string dimacs_file, string out_file_name);


private:
    Model s;
    void GenerateVariables(VECT_UINT &v, int k);
    void General(VECT_UINT &variables, unsigned int &k, unsigned int group_factor);
    void BimanderBinaryO(unsigned int m, unsigned int nb_elem, unsigned int k, unsigned int upper_log_m, VECT_UINT &variables);
    void BimanderBinaryK(unsigned int m, unsigned int nb_elem, unsigned int k, unsigned int upper_log_m, VECT_UINT &variables);
    void Binary(VECT_UINT &variables, unsigned int &k);
    void ALO(VECT_UINT &variables, unsigned int c_value = 0);
    void AMK_Pairwise(VECT_UINT &variables, unsigned int &k);
    TABLE_LIT RecursivePairing(unsigned int top_offset, unsigned int val, VECT_UINT &variables);


};

#endif
