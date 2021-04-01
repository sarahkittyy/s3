cmake_minimum_required(VERSION 3.18)
project(s3)

find_package(Catch2 REQUIRED)

file(GLOB sources "*.cpp")
add_executable(s3-test ${sources})
add_dependencies(s3-test s3)
target_link_libraries(s3-test s3 Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(s3-test)
