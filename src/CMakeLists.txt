project(proj)

add_executable(projq4.out
    minisat/Solver.cpp
    main4.cpp
    Problem4.cpp
)

add_executable(projq5.out
    minisat/Solver.cpp
    main5.cpp
    Problem4.cpp
    Problem5.cpp
)




list( APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g")

