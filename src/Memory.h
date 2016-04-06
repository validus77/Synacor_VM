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

struct Registers {
    std::uint16_t register_data[8];
    std::uint16_t& get_register(std::uint16_t address);
};

struct Memory{
    std::uint16_t memory_data[32767];
    std::uint16_t& get_memory(std::uint16_t address);
};
