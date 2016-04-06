//
// Created by Joshua Ritterman on 6/4/2016.
//

#include <sstream>
#include "Disassembler.h"

Disassembler::Disassembler(MemoryController& memoryController) : memoryController_(memoryController){

}

std::string Disassembler::printValue(std::uint16_t value) {
    std::stringstream ss;
    if(value <= 32767) {
        ss << "$" << value;
    } else if (value <= 32775) {
        ss << "%" << value - 32768;
    }
    return ss.str();
}
std::string Disassembler::printCharValue(std::uint16_t value) {
    std::stringstream ss;
    if(value <= 32767) {
        ss << static_cast<char>(value);
    } else {
        ss <<"";
    }
    return ss.str();
}

void Disassembler::printProgramStartingAt(std::uint16_t start_address, std::uint16_t end_address) {
    std::uint16_t address = start_address;
    while(address <= end_address) {
        std::cout << "Mem[" << address << "]: ";
        switch (memoryController_.readAtAddress(address)) {
            case 0:
                address += halt();
                break;
            case 1:
                address +=
                        set(memoryController_.readAtAddress(address + 1), memoryController_.readAtAddress(address + 2));
                break;
            case 2:
                address += push(memoryController_.readAtAddress(address + 1));
                break;
            case 3:
                address += pop(memoryController_.readAtAddress(address + 1));
                break;
            case 4:
                address +=
                        eq(memoryController_.readAtAddress(address + 1),
                           memoryController_.readAtAddress(address + 2),
                           memoryController_.readAtAddress(address + 3));
                break;
            case 5:
                address += gt(memoryController_.readAtAddress(address + 1),
                              memoryController_.readAtAddress(address + 2),
                              memoryController_.readAtAddress(address + 3));
                break;
            case 6:
                address += jump(memoryController_.readAtAddress(address + 1));
                break;
            case 7:
                address += jt(memoryController_.readAtAddress(address + 1),
                              memoryController_.readAtAddress(address + 2));
                break;
            case 8:
                address += jf(memoryController_.readAtAddress(address + 1),
                              memoryController_.readAtAddress(address + 2));
                break;
            case 9:
                address += add(memoryController_.readAtAddress(address + 1),
                               memoryController_.readAtAddress(address + 2),
                               memoryController_.readAtAddress(address + 3));
                break;
            case 10:
                address += mult(memoryController_.readAtAddress(address + 1),
                                memoryController_.readAtAddress(address + 2),
                                memoryController_.readAtAddress(address + 3));
                break;
            case 11:
                address += mod(memoryController_.readAtAddress(address + 1),
                               memoryController_.readAtAddress(address + 2),
                               memoryController_.readAtAddress(address + 3));
                break;
            case 12:
                address += and_i(memoryController_.readAtAddress(address + 1),
                                 memoryController_.readAtAddress(address + 2),
                                 memoryController_.readAtAddress(address + 3));
                break;
            case 13:
                address += or_i(memoryController_.readAtAddress(address + 1),
                                memoryController_.readAtAddress(address + 2),
                                memoryController_.readAtAddress(address + 3));
                break;
            case 14:
                address += not_i(memoryController_.readAtAddress(address + 1),
                                 memoryController_.readAtAddress(address + 2));
                break;
            case 15:
                address += rmem(memoryController_.readAtAddress(address + 1),
                                memoryController_.readAtAddress(address + 2));
                break;
            case 16:
                address += wmem(memoryController_.readAtAddress(address + 1),
                                memoryController_.readAtAddress(address + 2));
                break;
            case 17:
                address += call(memoryController_.readAtAddress(address + 1));
                break;
            case 18:
                address += ret();
                break;
            case 19:
                address += out(memoryController_.readAtAddress(address + 1));
                break;
            case 21:
                address += noop();
                break;
            case 20:
                address += in(memoryController_.readAtAddress(address + 1));
                break;
            default:
                std::cout << "Data -> " << memoryController_.readAtAddress(address) << std::endl;
                address += 1;
        }
    }
}


// OP CODES
std::int32_t Disassembler::halt() {
        std::cout << "OP_HALT" << std::endl;
    return 1;
}

std::int32_t Disassembler::set(std::uint16_t a, std::uint16_t b) {
    std::cout << "OP_SET " << printValue(a)<<"  " << printValue(b) << std::endl;
    return 3;
}

std::int32_t Disassembler::push(std::uint16_t a) {
    std::cout << "OP_PUSH " << printValue(a) << std::endl;
    return 2;
}
std::int32_t Disassembler::pop(std::uint16_t a) {
    std::cout << "OP_POP " << printValue(a) << std::endl;
    return 2;
}
std::int32_t Disassembler::eq(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
    std::cout << "OP_EQ " << printValue(a)<< "  " << printValue(b) <<
        "  " << printValue(c) << std::endl;
    return 4;
}
std::int32_t Disassembler::gt(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
    std::cout << "OP_GT " << printValue(a)<< "  " << printValue(b) <<
        "  " << printValue(c) << std::endl;
    return 4;
}
std::int32_t Disassembler::jump(std::uint16_t a) {
    std::cout << "OP_JMP " << printValue(a) << std::endl;
    return 2;
}
std::int32_t Disassembler::jt(std::uint16_t a, std::uint16_t b) {
    std::cout << "OP_JT " << printValue(a) << " " << printValue(b) << std::endl;
    return 3;
}
std::int32_t Disassembler::jf(std::uint16_t a, std::uint16_t b) {
    std::cout << "OP_JF " << printValue(a) << " " << printValue(b) << std::endl;
    return  3;
}
std::int32_t Disassembler::add(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
    std::cout << "OP_ADD " << printValue(a)<< "  " << printValue(b) <<
        "  " << printValue(c) << std::endl;
    return 4;
}
std::int32_t Disassembler::mult(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
    std::cout << "OP_MULT " << printValue(a)<< "  " << printValue(b) <<
        "  " << printValue(c) << std::endl;
    return 4;
}
std::int32_t Disassembler::mod(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
    std::cout << "OP_MOD " << printValue(a)<< "  " << printValue(b) <<
        "  " << printValue(c) << std::endl;
    return 4;
}
std::int32_t Disassembler::and_i(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
    std::cout << "OP_AND " << printValue(a)<< "  " << printValue(b) <<
        "  " << printValue(c) << std::endl;
    return 4;
}
std::int32_t Disassembler::or_i(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
        std::cout << "OP_OR " << printValue(a)<< "  " << printValue(b) <<
        "  " << printValue(c) << std::endl;
    return 4;
}
std::int32_t Disassembler::not_i(std::uint16_t a, std::uint16_t b) {
    std::cout << "OP_NOT " << printValue(a)<< "  " << printValue(b) << std::endl;
    return 3;
}
std::int32_t Disassembler::rmem(std::uint16_t a, std::uint16_t b) {
    std::cout << "OP_RMEM " << printValue(a)<< "  " << printValue(b) << std::endl;
    return 3;
}
std::int32_t Disassembler::wmem(std::uint16_t a, std::uint16_t b) {
    std::cout << "OP_WMEM " << printValue(b) << "  " << printValue(a) << std::endl;
    return 3;
}
std::int32_t Disassembler::call(std::uint16_t a) {
    std::cout << "OP_CALL " << printValue(a) << std::endl;
    return 2;
}
std::int32_t Disassembler::ret() {
    std::cout << "OP_RET " << std::endl;
    return 1;
}

std::int32_t Disassembler::out(std::uint16_t a) {
    std::cout << "OP_OUT " <<  printValue(a) <<  " [" << printCharValue(a) << "]" << std::endl;
    return 2;
}

std::int32_t Disassembler::in(std::uint16_t a) {
    std::cout << "OP_IN " <<  printValue(a) << std::endl;
    return 2;
}
std::int32_t Disassembler::noop() {
    std::cout << "OP_NOOP " << std::endl;
    return 1;
}
