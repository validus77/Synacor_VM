//
// Created by Joshua Ritterman on 6/4/2016.
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

#include "MemoryController.h"
#include "Debugger.h"

class VirtualCPU {
public:
    VirtualCPU(MemoryController& memoryController, std::stack<std::uint16_t>& stack);
    std::uint16_t executeInstructionAtAddress(std::uint16_t address);
private:

    // List of instructions
    std::int32_t halt();
    std::int32_t set(std::uint16_t a, std::uint16_t b);
    std::int32_t push(std::uint16_t a);
    std::int32_t pop(std::uint16_t a);
    std::int32_t eq(std::uint16_t a, std::uint16_t b, std::uint16_t c);
    std::int32_t gt(std::uint16_t a, std::uint16_t b, std::uint16_t c);
    std::int32_t jump(std::uint16_t a, std::uint16_t adr);
    std::int32_t jt(std::uint16_t a, std::uint16_t b, std::uint16_t adr);
    std::int32_t jf(std::uint16_t a, std::uint16_t b, std::uint16_t adr);
    std::int32_t add(std::uint16_t a, std::uint16_t b, std::uint16_t c);
    std::int32_t mult(std::uint16_t a, std::uint16_t b, std::uint16_t c);
    std::int32_t mod(std::uint16_t a, std::uint16_t b, std::uint16_t c);
    std::int32_t and_i(std::uint16_t a, std::uint16_t b, std::uint16_t c);
    std::int32_t or_i(std::uint16_t a, std::uint16_t b, std::uint16_t c);
    std::int32_t not_i(std::uint16_t a, std::uint16_t b);
    std::int32_t rmem(std::uint16_t a, std::uint16_t b);
    std::int32_t wmem(std::uint16_t a, std::uint16_t b);
    std::int32_t call(std::uint16_t a,std::uint16_t adr);
    std::int32_t ret();
    std::int32_t out(std::uint16_t a);
    std::int32_t in(std::uint16_t a);
    std::int32_t noop();



    MemoryController& memoryController_;
    std::stack<std::uint16_t>& stack_;

    Debugger debugger_;

};
