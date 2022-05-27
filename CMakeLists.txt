cmake_minimum_required(VERSION 3.18)

project(TST
	VERSION 0.0.1
	DESCRIPTION "Unit tests for C++ code"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(tst STATIC)

target_include_directories(tst
	PRIVATE
		Include/tst
	PUBLIC
		Include/
)

target_compile_options(tst
	PRIVATE
)

add_subdirectory(Src/)