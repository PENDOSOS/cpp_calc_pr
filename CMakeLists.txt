cmake_minimum_required(VERSION 3.20)
									
project(calc)				

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_HEADERS src/calculator.h src/number.h src/plugin_manager.h)
add_executable(calc src/main.cpp src/calculator.cpp src/number.cpp src/plugin_manager.cpp)


 