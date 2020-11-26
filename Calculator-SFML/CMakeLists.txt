cmake_minimum_required(VERSION 3.1)
project(Calculator-SFML)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/Samsung/Desktop/C++/SFML-master/SFML-2.5.1")
find_package(SFML 2.5.1 COMPONENTS system window graphics)
add_executable(Calculator-SFML main.cpp Button.cpp Button.hpp Tapplication.cpp Tapplication.hpp Tcalculator.cpp Tcalculator.hpp Tmath.cpp Tmath.hpp Tscreen.cpp Tscreen.hpp)
target_link_libraries(Calculator-SFML sfml-system sfml-window sfml-graphics)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14")
