cmake_minimum_required(VERSION 3.2)
project(infofond_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/minisat/Global.hpp
    src/minisat/Heap.hpp
    src/minisat/Solver.cpp
    src/minisat/Solver.hpp
    src/minisat/SolverTypes.hpp
    src/minisat/Sort.hpp
    src/minisat/VarOrder.hpp
    src/parser/main.cpp
    src/parser/parser.hpp
    src/parser/SchedSpec.hpp
    src/example.cpp
    src/example.hpp
    src/main4.cpp
    src/Problem4.cpp
    src/Problem4.hpp
    src/Writer.cpp
    src/Writer.hpp)

add_executable(infofond_project ${SOURCE_FILES} src/example2.hpp src/example2.h src/example2.cpp)