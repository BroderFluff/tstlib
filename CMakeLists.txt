cmake_minimum_required(VERSION 3.18)

project(TST
	VERSION 0.0.1
	DESCRIPTION "Unit tests for C++ code"
	LANGUAGES CXX
)

add_library(tst STATIC)

#add_executable(tst "")

target_compile_features(tst
	PRIVATE
		cxx_std_20
)

target_include_directories(tst
	PRIVATE
		Include/tst
	PUBLIC
		Include/
)

add_subdirectory(Src/)