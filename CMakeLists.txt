cmake_minimum_required(VERSION 3.18)

project(Testy
	VERSION 0.0.1
	DESCRIPTION "Unit tests for C++ code"
	LANGUAGES CXX
)

add_library(Testy STATIC)

target_include_directories(Testy
	PRIVATE
		Include/testy
)