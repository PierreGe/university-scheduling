project(proj)

# Nécessaire pour que Minisat compile
add_executable(proj
    minisat/Solver.cpp

    main.cpp
    parser/parser.cpp
    problem.cpp
)

