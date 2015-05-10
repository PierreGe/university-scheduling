#include "parser/parser.hpp"
#include "parser/SchedSpec.hpp"
#include "Problem.hpp"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Should give a file or string" << std::endl;
        exit(1);
    }
    std::string args(argv[1]);
    SchedSpec* specs = parse(args);
    Problem1 problem1(*specs);
    problem1.test();
    // delete specs;
}