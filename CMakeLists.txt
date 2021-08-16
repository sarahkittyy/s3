cmake_minimum_required(VERSION 3.18)
project(s3)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "Build the tests." ON)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
include(FindOpenGL)

file(GLOB_RECURSE sources "src/*.cpp")

add_library(s3 ${sources})

if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(test/)
endif()

if(BUILD_SANDBOX)
	add_subdirectory(sandbox/)
endif()

target_compile_options(s3 PUBLIC -Wall)
target_include_directories(s3 PUBLIC
	"include/"
	PRIVATE
	"src/"
	"libs/"
	${ASSIMP_INCLUDE_DIRS}
)
target_link_libraries(s3
	glfw GLEW GL ${ASSIMP_LIBRARIES}
)
