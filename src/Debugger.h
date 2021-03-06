//
// Created by joshua on 4/7/16.
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
#include <set>
#include <vector>

#include "MemoryController.h"
#include "Disassembler.h"

class Debugger {
 public:
  Debugger(MemoryController& memoryController, std::stack<std::uint16_t>& stack);

  bool shouldBrake(std::uint16_t address);
  void debugConsole(std::uint16_t address);
  void setBreakPoint(std::uint16_t address);
  void clearBreakPoint(std::uint16_t address);

  std::uint16_t pc_; // this is a hack;
 private:
  void printMemory(std::uint16_t address);
  void printCodeBlockAt(std::uint16_t address);
  void printStack(std::stack<std::uint16_t> &s);
  void printRegisters();
  void continueExec();
  void printHelp();
  void setRegester(std::uint16_t id, std::uint16_t value);
  void setMemeory(std::uint16_t address, std::uint16_t value);

  std::vector<std::string> split(const std::string &s, char delim);

  bool in_trace_;

  std::set<std::uint16_t> break_points_;
  MemoryController& memoryController_;
  std::stack<std::uint16_t>& stack_;
  Disassembler disassembler_;
};