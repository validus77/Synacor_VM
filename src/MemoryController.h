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

#include "Memory.h"

class MemoryController {
public:
    MemoryController(Registers& registers, Memory& memory);

    std::uint16_t readAtAddress(uint16_t address);
    std::uint16_t& accessAtAddress(uint64_t address);
    std::uint16_t readValue(uint16_t value);

     // Debuger output
    std::string decodeValue(uint16_t value);
    std::string decodeMemory(uint16_t address);
private:
    Registers& registers_;
    Memory& memory_;

};
