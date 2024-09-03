cmake_minimum_required(VERSION 3.28)
project(SFML_Graphics_testing)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")


find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)

add_executable(SFML_Graphics_testing main.cpp)

target_link_libraries(SFML_Graphics_testing sfml-system sfml-window sfml-graphics sfml-audio)
