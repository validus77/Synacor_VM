cmake_minimum_required(VERSION 3.5)
project(VM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp src/Memory.cpp src/Memory.h src/VirtualMachine.cpp src/VirtualMachine.cpp
        src/VirtualMachine.h src/MemoryController.cpp src/MemoryController.h src/VirtualCPU.cpp src/VirtualCPU.h
        src/Disassembler.cpp src/Disassembler.h src/Debugger.cpp src/Debugger.h)
add_executable(VM ${SOURCE_FILES})