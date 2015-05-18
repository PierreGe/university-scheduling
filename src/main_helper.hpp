#include "parser/parser.hpp"
#include "parser/SchedSpec.hpp"
#include "Problem9.hpp"

#include <iostream>
#include <string>

template<typename T>
int main_helper(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Utilisation :  " << argv[0]  <<" [file or string]" << std::endl;
        exit(1);
    }
    std::string args(argv[1]);
    try {
        SchedSpec* specs = parse(args);
        T problem(*specs);
        problem.solve();
        if (problem.okay()) {
            std::cout << "Success, the problem has been solve under those constraints !" << std::endl;
        }
        else {
            std::cout << "Uh .. The problem could not be solve under those constraints" << std::endl;
            exit(1);
        }
        problem.output();
    }
    catch(const char* error)
    {
        std::cerr<<"Error: "<<error<<std::endl;
    }
    catch(...)
    {
        std::cerr<<"Unknown error"<<std::endl;
    }
    return 0;
}