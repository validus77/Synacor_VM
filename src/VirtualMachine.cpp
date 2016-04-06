//
// Created by Joshua Ritterman on 5/4/2016.
//

#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() :
        program_cursor_(0),
        memoryController_(registers_, memeory_),
        virtualCPU_(memoryController_, stack_),
        disassembler_(memoryController_){

}

void VirtualMachine::LoadProgram(std::string file_name) {
    std::cout << "Start reading file: " << file_name << std::endl;
    FILE *file;
    file = fopen(file_name.c_str(), "rb");

    uint16_t buffer;
    uint16_t load_index  = 0;

    struct stat st;
    stat(file_name.c_str(), &st);
    auto size = st.st_size;

    for (int i = 0; i < size / sizeof(uint16_t); i++) {
        fread(&buffer, sizeof(uint16_t), 1, file);
        memeory_.get_memory(i) = buffer;
    }
}

void VirtualMachine::LoadDisassemble(std::string file_name) {
    FILE *file;
    file = fopen(file_name.c_str(), "rb");
    uint16_t buffer;
    struct stat st;
    stat(file_name.c_str(), &st);
    auto size = st.st_size;
    for (int i = 0; i < size / sizeof(uint16_t); i++) {
        fread(&buffer, sizeof(uint16_t), 1, file);
        memeory_.get_memory(i) = buffer;
    }
    disassembler_.printProgramStartingAt(0, size);
}


void VirtualMachine::run() {
    while(program_cursor_ < 32775) {
        program_cursor_ = virtualCPU_.executeInstructionAtAddress(program_cursor_);
    }
}
