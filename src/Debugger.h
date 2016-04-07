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

#include "MemoryController.h"
#include "Disassembler.h"

class Debugger {
 public:
  Debugger(MemoryController& memoryController);

  bool shouldBrake(std::uint16_t address);
  void debugConsole(std::uint16_t address);
  void setBreakPoint(std::uint16_t address);
  void clearBreakPoint(std::uint16_t address);

  std::uint16_t pc_; // this is a hack;
 private:
  void printMemory(std::uint16_t address);
  void printCodeBlockAt(std::uint16_t address);
  void printCodeAt(std::uint16_t address);
  void printRegisters();
  void continueExec();
  void printHelp();

  bool in_trace_;

  std::set<std::uint16_t> break_points_;
  MemoryController& memoryController_;
  Disassembler disassembler_;
};