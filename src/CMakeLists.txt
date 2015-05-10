project(proj)

# Nécessaire pour que Minisat compile
add_executable(proj
    minisat/Solver.cpp
    main.cpp
    Problem.cpp
)

list( APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g")

