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

add_executable(projq6.out
    minisat/Solver.cpp
    main6.cpp
    Problem4.cpp
    Problem5.cpp
    Problem6.cpp
)

add_executable(projq7.out
    minisat/Solver.cpp
    main7.cpp
    Problem4.cpp
    Problem5.cpp
    Problem6.cpp
    Problem7.cpp
)




list( APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g")

