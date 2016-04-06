//
// Created by Joshua Ritterman on 5/4/2016.
//

#include <sstream>
#include "MemoryController.h"


MemoryController::MemoryController(Registers& registers, Memory& memory) :
registers_(registers), memory_(memory){

}

std::uint16_t MemoryController::readAtAddress(uint16_t address) {
   if(address <= 32767) {
       return memory_.get_memory(address);
   } else if (address <= 32775) {
       return registers_.get_register(address);
   } else {
       std::cout << "MemoryController error illegal address: " << address << std::endl;
   }
    return 0;
}

std::uint16_t& MemoryController::accessAtAddress(uint64_t address) {
    if(address <= 32767) {
        return memory_.get_memory(address);
    } else if (address <= 32775) {
        return registers_.get_register(address);
    } else {
        std::cout << "MemoryController error illegal address: " << address << std::endl;
    }
    memory_.get_memory(0);
}

std::uint16_t MemoryController::readValue(uint16_t value) {
    if(value <= 32767) {
        return value;
    } else if (value <= 32775) {
        return registers_.get_register(value);
    } else {
        std::cout << "MemoryController illegal value: " << value << std::endl;
    }
    return 0;
}

std::string MemoryController::decodeValue(uint16_t value) {
  std::stringstream ss;
  if(value <= 32767) {
    ss << "$" << value;
  } else if (value <= 32775) {
    ss << "%" << value - 32768 << "[" << readValue(value) <<"]";
  }
  return ss.str();
}

std::string MemoryController::decodeMemory(uint16_t address) {
  std::stringstream ss;
  ss << "@" << address <<"[" << readAtAddress(address) << "]";
  return ss.str();
}