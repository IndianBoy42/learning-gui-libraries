cmake_minimum_required(VERSION 3.16)

project(sfml-play)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_EXTENSIONS ON)

find_package(SFML 2 REQUIRED
    graphics window system)

add_executable(sfml_play main.cpp)
target_include_directories(sfml_play PUBLIC ./ ${SFML_INCLUDE_PATH})
# target_link_libraries(sfml_play PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(sfml_play PUBLIC sfml-graphics)
# lots of warnings and all warnings as errors
target_compile_options(sfml_play PUBLIC -march=native -mtune=native -mavx -mavx2) target_compile_options(sfml_play PUBLIC -Wall -Wuninitialized -Wextra -Wpedantic)
target_link_libraries(sfml_play PUBLIC m pthread)
target_compile_options(sfml_play PUBLIC -fopenmp)
add_custom_target(run_sfml_play  sfml)
