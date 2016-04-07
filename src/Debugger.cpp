//
// Created by joshua on 4/7/16.
//

#include <sstream>
#include <vector>
#include "Debugger.h"

Debugger::Debugger(MemoryController& memoryController, std::stack<std::uint16_t>& stack) :
    in_trace_(false),
    memoryController_(memoryController),
    disassembler_(memoryController),
    stack_(stack){

}

void Debugger::debugConsole(std::uint16_t address) {
  std::cout << "Debugger [" << pc_<< "]> ";
  std::string command;
  std::getline( std::cin, command);

  std::vector<std::string> command_list = split(command, ' ');

  if(command_list.front() == "help") {
    printHelp();
  } else if (command_list.front() == "c") {
    continueExec();
    return;
  } else if (command_list.front() == "pr") {
    printRegisters();
  } else if (command_list.front() == "pm") {
    uint16_t addr = (command_list.size() == 2)? atoi(command_list[1].c_str()) : pc_;
    printMemory(addr);
  } else if (command_list.front() == "ps") {
      std::cout << "--Stack--" << std::endl;
      printStack(stack_);
  } else if (command_list.front() == "disa") {
    uint16_t addr = (command_list.size() == 2)? atoi(command_list[1].c_str()) : pc_;
    printCodeBlockAt(addr);
  } else if(command_list.front() == "br") {
    uint16_t addr = (command_list.size() == 2)? atoi(command_list[1].c_str()) : pc_;
    setBreakPoint(addr);
  } else if(command_list.front() == "cbr") {
    uint16_t addr = (command_list.size() == 2)? atoi(command_list[1].c_str()) : pc_;
    clearBreakPoint(addr);
  } else if(command_list.front() == "setr") {
    setRegester(atoi(command_list[1].c_str()), atoi(command_list[2].c_str()));
  } else if(command_list.front() == "setm") {
    setMemeory(atoi(command_list[1].c_str()), atoi(command_list[2].c_str()));
  } else if(command_list.front() == "push") {
      stack_.push(atoi(command_list[1].c_str()));
  } else if(command_list.front() == "pop") {
      stack_.pop();
  } else if (command_list.front() == "s") {
    return;
  } else {
    std::cout << "Unknowen command type 'help' for list of comamnds" << std::endl;
  }
  debugConsole(pc_);
  return;
}

void Debugger::setBreakPoint(std::uint16_t address) {
  break_points_.insert(address);
  std::cout << "Breakpoint set at " << address << std::endl;
}

void Debugger::clearBreakPoint(std::uint16_t address) {
  break_points_.erase(address);
  std::cout << "Breakpoint removed at " << address << std::endl;

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

void Debugger::printMemory(std::uint16_t address) {
  std::cout << pc_ << ": " << memoryController_.readAtAddress(pc_) << std::endl;
}

void Debugger::continueExec() {
  in_trace_ = false;
}

void Debugger::setRegester(std::uint16_t id, std::uint16_t value) {
  if(id > 8) {
    std::cout << "Error %" << id << " is invalid there are 8 regesters" << std::endl;
    return;
  }
  memoryController_.accessAtAddress(id + 32768) = value;
}

void Debugger::setMemeory(std::uint16_t address, std::uint16_t value) {
  if(address > 8) {
    std::cout << "Error [" << address << "] is invalid" << std::endl;
    return;
  }
  memoryController_.accessAtAddress(address) = value;
}
void Debugger::printHelp() {
  std::cout << "Debugger commands:" << "" << std::endl
      << "    c - continue execution" << std::endl
      << "    pr - print regesters" << std::endl
      << "    pm [mem_addr] - print memeory adress" << std::endl
      << "    ps - print the stack " << std::endl
      << "    disa [mem_addr] - dissasemble code starting at addr" << std::endl
      << "    br [mem_addr] - set breakpoint" << std::endl
      << "    cbr [mem_addr] - clear breakpoint" << std::endl
      << "    setr [regester] [value] - set a regester value" << std::endl
      << "    setm [mem_addr] [value] - set a regester value" << std::endl
      << "    push [value] - push a value on to the stack" << std::endl
      << "    pop - pop a value from the stack" << std::endl
      << "    s - step to next instruction" << std::endl;
}

std::vector<std::string> Debugger::split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> tokens;
  while (getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}
void Debugger::printStack(std::stack<std::uint16_t> &s) {
    if(s.empty())
    {
        std::cout << std::endl;
        return;
    }
    std::uint16_t x= s.top();
    s.pop();
    printStack(s);
    s.push(x);
    std::cout << x << std::endl;
}