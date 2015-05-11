#include "parser/parser.hpp"
#include "parser/SchedSpec.hpp"
#include "Problem.hpp"

#include <iostream>
#include <string>

void test() {
    std::string args("2 ;3 ;1 ;10 ;50 ;2 ;2 ;2 ;1,2 ;1 ;1 ;2 ;");
    SchedSpec* specs = parse(args);
    Problem1 problem1(*specs);
    problem1.test();
}

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
        Problem1 problem1(*specs);
        problem1.solve();
        if (problem1.okay()) {
            std::cout << "Success, the problem has been solve under those constraints !" << std::endl;
            problem1.display();
        }
        else {
            std::cout << "Uh .. The problem could not be solve under those constraints" << std::endl;
        }
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