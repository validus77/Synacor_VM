//
// Created by Joshua Ritterman on 5/4/2016.
//
#pragma once
#include <iostream>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <stack>

#include "Memory.h"
#include "MemoryController.h"
#include "VirtualCPU.h"
#include "Disassembler.h"

class VirtualMachine {
public:
    VirtualMachine();

    void LoadProgram(std::string file_name);
    void LoadDisassemble(std::string file_name);

    void run();

private:

    std::uint16_t program_cursor_;
    Registers registers_;
    Memory memeory_;
    MemoryController memoryController_;
    std::stack<uint16_t> stack_;
    VirtualCPU virtualCPU_;
    Disassembler disassembler_;
};
