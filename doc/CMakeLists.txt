cmake_minimum_required(VERSION 2.8)
project(ss)

include_directories(../src/assembler/h)
include_directories(../src/instructions/h)


file(GLOB SOURCE_FILES_ASSEMBLER
        ../src/assembler/h/*.h
        ../src/assembler/src/*.cpp
	
        )

file(GLOB SOURCE_FILES_INSTRUCTIONS
	../src/instructions/h/*.h
	../src/instructions/src/*.cpp
	)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


add_executable(ss ${SOURCE_FILES_ASSEMBLER} ${SOURCE_FILES_INSTRUCTIONS})





