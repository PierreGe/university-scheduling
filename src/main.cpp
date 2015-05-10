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
    test();
    if (argc < 2) {
        std::cout << "Should give a file or string" << std::endl;
        exit(1);
    }
    std::string args(argv[1]);
    SchedSpec* specs = parse(args);
    Problem1 problem1(*specs);
    problem1.solve();
    if (problem1.okay()) {
        std::cout << "okay" << std::endl;
    }
    else {
        std::cout << "not okay" << std::endl;
    }
    return 0;
}