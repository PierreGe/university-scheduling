#include "parser/parser.hpp"
#include "parser/SchedSpec.hpp"
#include "Problem6.hpp"

#include <iostream>
#include <string>


int main(int argc, char **argv)
{
    //test();
    if (argc < 2) {
        std::cout << "Utilisation :  " << argv[0]  <<" [file or string]" << std::endl;
        exit(1);
    }
    std::string args(argv[1]);
    try {
        SchedSpec* specs = parse(args);
        Problem6 problem(*specs);
        problem.solve();
        if (problem.okay()) {
            std::cout << "Success, the problem has been solve under those constraints !" << std::endl;
        }
        else {
            std::cout << "Uh .. The problem could not be solve under those constraints" << std::endl;
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