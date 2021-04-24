cmake_minimum_required(VERSION 3.16)

project(raylib-play)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_EXTENSIONS ON)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(raylib 3.0 QUIET) # Requires at least version 2.5.0
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    # URL https://github.com/raysan5/raylib/archive/master.tar.gz
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG e25e380e80a117f2404d65b37700fb620dc1f990
    GIT_SHALLOW 1
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

find_package(raylib-cpp 3.5.0 QUIET)
if (NOT raylib-cpp_FOUND)
    include(FetchContent)
        FetchContent_Declare(
        raylib-cpp
        # URL https://github.com/RobLoach/raylib-cpp/archive/master.tar.gz
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG 21d26ca66e3a8fc70a39ad13b40dcabbc1840a78
        GIT_SHALLOW 1
    )
    FetchContent_GetProperties(raylib-cpp)
    if (NOT raylib-cpp_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib-cpp)
        set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_TESTING             OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib-cpp_SOURCE_DIR} ${raylib-cpp_BINARY_DIR})
    endif()
endif()
  
set(raylib_VERBOSE 1)  

add_executable(raylib_play main.cpp)
target_link_libraries(raylib_play PUBLIC raylib raylib-cpp)
target_include_directories(raylib_play PUBLIC . inc)
# target_link_libraries(raylib_play PUBLIC OpenMP::OpenMP_CXX)
# lots of warnings and all warnings as errors
target_compile_options(raylib_play PUBLIC -march=native -mtune=native -mavx -mavx2)
target_compile_options(raylib_play PUBLIC -Wall -Wuninitialized -Wextra -Wpedantic)
target_link_libraries(raylib_play PUBLIC m pthread)
target_compile_options(raylib_play PUBLIC -fopenmp)
add_custom_target(run raylib_play)
