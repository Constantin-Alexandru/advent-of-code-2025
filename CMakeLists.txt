cmake_minimum_required(VERSION 3.30)
project(advent_of_code VERSION 1.0.0 DESCRIPTION "My Advent of Code entry.")

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_executable(${PROJECT_NAME} src/problem1.cpp src/problem2.cpp src/problem3.cpp src/main.cpp)

target_include_directories(${PROJECT_NAME}
			PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
)

target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CONFIG:Debug>:-Wall -Wextra -Werror -Wpedantic -O3>
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
