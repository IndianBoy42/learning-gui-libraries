cmake_minimum_required(VERSION 3.16)

project(sfml-play)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_EXTENSIONS ON)

find_package(SFML 2 REQUIRED
    network audio graphics window system)

add_executable(sfml main.cpp)
target_include_directories(sfml PUBLIC ./ ${SFML_INCLUDE_PATH})
#    target_link_libraries(sfml PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(sfml PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
# lots of warnings and all warnings as errors
    target_compile_options(sfml PUBLIC -march=native -mtune=native -mavx -mavx2)
    target_compile_options(sfml PUBLIC -Wall -Wuninitialized -Wextra -Wpedantic)
    target_link_libraries(sfml PUBLIC m)
    target_link_libraries(sfml PUBLIC stdc++ m pthread)
target_compile_options(sfml PUBLIC -fopenmp)
add_custom_target(run_sfml mpirun -n 2 --oversubscribe sfml)
