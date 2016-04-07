//
// Created by joshua on 4/7/16.
//

#include "Debugger.h"
Debugger::Debugger(MemoryController& memoryController) :
    in_trace_(false),
    memoryController_(memoryController),
    disassembler_(memoryController){

}

void Debugger::debugConsole(std::uint16_t address) {
  std::cout << "Debugger > ";
  std::string command;
  std::cin >> command;

  if(command == "help") {
    printHelp();
  } else if (command == "c") {
    continueExec();
    return;
  } else if (command == "pr") {
    printRegisters();
  } else if (command == "pm") {
    printMemory(pc_);
  } else if (command == "disa") {
    printCodeBlockAt(pc_);
  } else if (command == "s") {
    return;
  } else {
    std::cout << "Unknowen command type 'help' for list of comamnds" << std::endl;
  }
  debugConsole(pc_);
  return;
}

void Debugger::setBreakPoint(std::uint16_t address) {
  break_points_.insert(address);
}

void Debugger::clearBreakPoint(std::uint16_t address) {
  break_points_.erase(address);

}

bool Debugger::shouldBrake(std::uint16_t address) {
  bool ret = in_trace_ || (break_points_.find(pc_) != break_points_.end());
  in_trace_ = ret;
  return ret;
}

void Debugger::printRegisters() {
  for(int i = 0; i < 8; i++) {
    std::cout <<"%" << i << " = " << memoryController_.readAtAddress(i + 32768) << std::endl;
  }
}

void Debugger::printCodeBlockAt(std::uint16_t address) {
  disassembler_.printProgramStartingAt(pc_, pc_ + 10);
}

void Debugger::printCodeAt(std::uint16_t address) {
  disassembler_.printProgramStartingAt(pc_, pc_ + 1);
}

void Debugger::printMemory(std::uint16_t address) {
  std::cout << pc_ << ": " << memoryController_.readAtAddress(pc_) << std::endl;
}

void Debugger::continueExec() {
  in_trace_ = false;
}

void Debugger::printHelp() {
  std::cout << "Debugger commands:" << "" << std::endl
      << "    c - continue execution" << std::endl
      << "    pr - print regesters" << std::endl
      << "    pm [mem_addr] - print memeory adress" << std::endl
      << "    disa [mem_addr] - dissasemble code starting at addr" << std::endl
      << "    s - step to next instruction" << std::endl;
}