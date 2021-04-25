cmake_minimum_required(VERSION 3.16)

project(sfml-play)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_C_EXTENSIONS ON)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(SFML 2.5 REQUIRED
    graphics window system)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(IMGUI_DIR "${CMAKE_CURRENT_LIST_DIR}/../imgui"
CACHE PATH "Location of Dear ImGUI" )
file(GLOB imgui_srcs ${IMGUI_DIR}/*.cpp)
# set(IMGUI_BACKEND "sfml" CACHE PATH "Chosen backend for ImGUI")
# file(GLOB imgui_backend_srcs ${IMGUI_DIR}/backends/imgui_imp_${IMGUI_BACKEND}*)
# set(imgui_srcs ${imgui_srcs} ${imgui_backend_srcs})
set(IMGUI_INCLUDE_DIR ${IMGUI_DIR})
set(imgui_incs ${IMGUI_DIR} imgui-sfml)
file(GLOB imgui_backend_srcs imgui-sfml/*)
set(imgui_srcs ${imgui_srcs} ${imgui_backend_srcs})

add_subdirectory(imgui-plot)

add_executable(sfml_play main.cpp ${imgui_srcs})
target_include_directories(sfml_play PUBLIC . inc ${imgui_incs})
target_include_directories(sfml_play PUBLIC ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
# target_link_libraries(sfml_play PUBLIC OpenMP::OpenMP_CXX)
# lots of warnings and all warnings as errors
target_compile_options(sfml_play PUBLIC -march=native -mtune=native -mavx -mavx2)
target_compile_options(sfml_play PUBLIC -Wall -Wuninitialized -Wextra -Wpedantic)
target_link_libraries(sfml_play PUBLIC m pthread)
target_include_directories(sfml_play PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(sfml_play PUBLIC sfml-graphics ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_compile_options(sfml_play PUBLIC -fopenmp)
# qt5_use_modules(sfml_play Widgets)

add_custom_target(run sfml_play)