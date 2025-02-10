cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(testcase)

find_package(Torch REQUIRED)

add_executable(testcase testcase.cpp)
target_link_libraries(testcase "${TORCH_LIBRARIES}")
set_property(TARGET testcase PROPERTY CXX_STANDARD 17)