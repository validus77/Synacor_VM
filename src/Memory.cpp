//
// Created by Joshua Ritterman on 5/4/2016.
//

#include "Memory.h"

std::uint16_t& Registers::get_register(std::uint16_t address) {
std::uint16_t index = address - 32768;
if(index > 8) {
    std::cout << "ERROR invalid register: " << index << std::endl;
exit(-1);
}
return register_data[index];
}

std::uint16_t& Memory::get_memory(std::uint16_t address) {
    if(address > 32768) {
        std::cout << "ERROR invalid Memory address: " << address << std::endl;
    }
    return memory_data[address];
}
