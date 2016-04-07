#include <iostream>
#include "VirtualMachine.h"

using namespace std;


int main(int argc, char** argv) {
    VirtualMachine computer;


    computer.LoadProgram("/home/joshua/Development/Synacor_VM/resource/challenge.bin");
    //computer.LoadDisassemble("/Users/jritterman/Code/Game/resource/challenge.bin");
    computer.run();
    return 0;
}