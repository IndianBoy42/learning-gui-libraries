cmake_minimum_required(VERSION 3.16)

project(blend2d-play)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_EXTENSIONS ON)

set(OpenGL_GL_PREFERENCE GLVND)

set(BLEND2D_STATIC TRUE)
set(BLEND2D_DIR "${CMAKE_CURRENT_LIST_DIR}/blend2d"
    CACHE PATH "Location of 'blend2d'")
add_subdirectory(${BLEND2D_DIR})
find_package(Qt5Widgets REQUIRED)
    
add_executable(blend2d_play main.cpp qblcanvas.cpp)
target_link_libraries(blend2d_play PUBLIC Qt5::Widgets Blend2D::Blend2D)
target_include_directories(blend2d_play PUBLIC . inc)
# target_link_libraries(blend2d_play PUBLIC OpenMP::OpenMP_CXX)
# lots of warnings and all warnings as errors
target_compile_options(blend2d_play PUBLIC -march=native -mtune=native -mavx -mavx2)
target_compile_options(blend2d_play PUBLIC -Wall -Wuninitialized -Wextra -Wpedantic)
target_link_libraries(blend2d_play PUBLIC m pthread)
target_compile_options(blend2d_play PUBLIC -fopenmp)
# qt5_use_modules(blend2d_play Widgets)

add_custom_target(run blend2d_play)