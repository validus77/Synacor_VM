//
// Created by Joshua Ritterman on 6/4/2016.
//

#include "VirtualCPU.h"

VirtualCPU::VirtualCPU(MemoryController& memoryController, std::stack<uint16_t>& stack) :
memoryController_(memoryController), stack_(stack) , debugger_(memoryController){
      debugger_.setBreakPoint(0);


}

std::uint16_t VirtualCPU::executeInstructionAtAddress(std::uint16_t address) {
  debugger_.pc_  = address; //HACK FOR NOW
    switch (memoryController_.readAtAddress(address)) {
        case 0:
            return address + halt();
        case 1:
            return address + set(memoryController_.readAtAddress(address + 1), memoryController_.readAtAddress(address + 2));
        case 2:
            return address + push(memoryController_.readAtAddress(address + 1));
        case 3:
            return address + pop(memoryController_.readAtAddress(address + 1));
        case 4:
            return address +
                    eq(memoryController_.readAtAddress(address + 1),
                       memoryController_.readAtAddress(address + 2),
                       memoryController_.readAtAddress(address + 3));
        case 5:
            return address + gt(memoryController_.readAtAddress(address + 1),
                                memoryController_.readAtAddress(address +2),
                                memoryController_.readAtAddress(address + 3));
        case 6:
            return jump(memoryController_.readAtAddress(address + 1), address);
        case 7:
            return jt(memoryController_.readAtAddress(address + 1),
                                memoryController_.readAtAddress(address + 2),
                                address);
        case 8:
            return jf(memoryController_.readAtAddress(address + 1),
                                memoryController_.readAtAddress(address + 2),
                                address);
        case 9:
            return address + add(memoryController_.readAtAddress(address + 1),
                                 memoryController_.readAtAddress(address + 2),
                                 memoryController_.readAtAddress(address + 3));
        case 10:
            return address + mult(memoryController_.readAtAddress(address + 1),
                                 memoryController_.readAtAddress(address + 2),
                                 memoryController_.readAtAddress(address + 3));
        case 11:
            return address + mod(memoryController_.readAtAddress(address + 1),
                                  memoryController_.readAtAddress(address + 2),
                                  memoryController_.readAtAddress(address + 3));
        case 12:
            return address + and_i(memoryController_.readAtAddress(address + 1),
                                 memoryController_.readAtAddress(address + 2),
                                 memoryController_.readAtAddress(address + 3));
        case 13:
            return address + or_i(memoryController_.readAtAddress(address + 1),
                                 memoryController_.readAtAddress(address + 2),
                                 memoryController_.readAtAddress(address + 3));
        case 14:
            return address + not_i(memoryController_.readAtAddress(address + 1),
                                 memoryController_.readAtAddress(address + 2));
        case 15:
            return address + rmem(memoryController_.readAtAddress(address + 1),
                                 memoryController_.readAtAddress(address + 2));
        case 16:
            return address + wmem(memoryController_.readAtAddress(address + 1),
                                  memoryController_.readAtAddress(address + 2));
        case 17:
            return call(memoryController_.readAtAddress(address + 1), address);
        case 18:
            return ret();
        case 19:
            return address + out(memoryController_.readAtAddress(address + 1));
        case 21:
            return address + noop();
        case 20:
            return address + in(memoryController_.readAtAddress(address + 1));
        default:
            std::cout << "CPU ERROR illegal op code: " << memoryController_.readAtAddress(address) << std::endl;
            return address + 1;
    }
}


// OP CODES
std::int32_t VirtualCPU::halt() {
    if(debugger_.shouldBrake(0)) {
      std::cout << "HALT" << std::endl;
      debugger_.debugConsole(0);
    }

    std::cout << "--CPU HALT--" << std::endl;
    exit(0);
}

std::int32_t VirtualCPU::set(std::uint16_t a, std::uint16_t b) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "SET " << memoryController_.decodeValue(a) << "  " << memoryController_.decodeValue(b) << std::endl;
    debugger_.debugConsole(0);
  }
  memoryController_.accessAtAddress(a) = memoryController_.readValue(b);
    return 3;
}

std::int32_t VirtualCPU::push(std::uint16_t a) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "PUSH " << memoryController_.decodeValue(a) << std::endl;
    debugger_.debugConsole(0);
  }
    stack_.push(memoryController_.readValue(a));
    return 2;
}
std::int32_t VirtualCPU::pop(std::uint16_t a) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "POP " << memoryController_.decodeValue(a) << std::endl;
    debugger_.debugConsole(0);
  }

  if(!stack_.empty()) {
    memoryController_.accessAtAddress(a) = stack_.top();
    stack_.pop();
  } else {
    std::cout << "ERROR pop called on empty stack" << std::endl;
  }
    return 2;
}
std::int32_t VirtualCPU::eq(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "EQ " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeValue(b) <<
        "  " << memoryController_.decodeValue(c) << std::endl;
    debugger_.debugConsole(0);
  }
    if(memoryController_.readValue(b) == memoryController_.readValue(c)) {
      memoryController_.accessAtAddress(a) = 1;
    } else {
      memoryController_.accessAtAddress(a) = 0;
    }
    return 4;
}
std::int32_t VirtualCPU::gt(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "GT " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeValue(b) <<
        "  " << memoryController_.decodeValue(c) << std::endl;
    debugger_.debugConsole(0);
  }
    if(memoryController_.readValue(b) > memoryController_.readValue(c)) {
      memoryController_.accessAtAddress(a) = 1;
    } else {
      memoryController_.accessAtAddress(a) = 0;
    }
    return 4;
}
std::int32_t VirtualCPU::jump(std::uint16_t a, std::uint16_t adr) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "JMP " << memoryController_.decodeValue(a) << std::endl;
    debugger_.debugConsole(0);
  }
    return memoryController_.readValue(a);
}
std::int32_t VirtualCPU::jt(std::uint16_t a, std::uint16_t b, std::uint16_t adr) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "JT " << memoryController_.decodeValue(a) << " " << memoryController_.decodeValue(b) << std::endl;
    debugger_.debugConsole(0);
  }
    if(memoryController_.readValue(a) != 0) {
        return memoryController_.readValue(b);
    }
    return adr + 3;
}
std::int32_t VirtualCPU::jf(std::uint16_t a, std::uint16_t b, std::uint16_t adr) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "JF " << memoryController_.decodeValue(a) << " " << memoryController_.decodeValue(b) << std::endl;
    debugger_.debugConsole(0);
  }

    if(memoryController_.readValue(a) == 0) {
        return memoryController_.readValue(b);
    }
    return adr + 3;
}
std::int32_t VirtualCPU::add(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "ADD " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeValue(b) <<
        "  " << memoryController_.decodeValue(c) << std::endl;
    debugger_.debugConsole(0);
  }
  memoryController_.accessAtAddress(a) = (memoryController_.readValue(b) + memoryController_.readValue(c)) % 32768;
    return 4;
}
std::int32_t VirtualCPU::mult(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "MULT " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeValue(b) <<
        "  " << memoryController_.decodeValue(c) << std::endl;
    debugger_.debugConsole(0);
  }
  memoryController_.accessAtAddress(a) = (memoryController_.readValue(b) * memoryController_.readValue(c)) % 32768;
    return 4;
}
std::int32_t VirtualCPU::mod(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "MOD " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeValue(b) <<
        "  " << memoryController_.decodeValue(c) << std::endl;
    debugger_.debugConsole(0);
  }

  memoryController_.accessAtAddress(a) = (memoryController_.readValue(b) % memoryController_.readValue(c));
    return 4;
}
std::int32_t VirtualCPU::and_i(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "AND " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeValue(b) <<
        "  " << memoryController_.decodeValue(c) << std::endl;
    debugger_.debugConsole(0);
  }
  memoryController_.accessAtAddress(a) = (memoryController_.readValue(b) & memoryController_.readValue(c));
    return 4;
}
std::int32_t VirtualCPU::or_i(std::uint16_t a, std::uint16_t b, std::uint16_t c) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "OR " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeValue(b) <<
        "  " << memoryController_.decodeValue(c) << std::endl;
    debugger_.debugConsole(0);
  }

  memoryController_.accessAtAddress(a) = (memoryController_.readValue(b) | memoryController_.readValue(c));
    return 4;
}
std::int32_t VirtualCPU::not_i(std::uint16_t a, std::uint16_t b) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "NOT " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeValue(b) << std::endl;
    debugger_.debugConsole(0);
  }
  memoryController_.accessAtAddress(a) = (~memoryController_.readValue(b))  & ((1 << 15) - 1);
    return 3;
}
std::int32_t VirtualCPU::rmem(std::uint16_t a, std::uint16_t b) {
  if(debugger_.shouldBrake(0)) {
    std::uint16_t val = memoryController_.readValue(b);
    std::cout << "RMEM " << memoryController_.decodeValue(a)<< "  " << memoryController_.decodeMemory(val) << std::endl;
    debugger_.debugConsole(0);
  }

  memoryController_.accessAtAddress(a) = memoryController_.readAtAddress(memoryController_.readValue(b));
    return 3;
}
std::int32_t VirtualCPU::wmem(std::uint16_t a, std::uint16_t b) {
  if(debugger_.shouldBrake(0)) {
    std::uint16_t val = memoryController_.readValue(a);
    std::cout << "WMEM " << memoryController_.decodeMemory(val)<< "  " << memoryController_.decodeValue(b) << std::endl;
    debugger_.debugConsole(0);
  }
  memoryController_.accessAtAddress(memoryController_.readValue(a)) = memoryController_.readValue(b);
  return 3;
}
std::int32_t VirtualCPU::call(std::uint16_t a, std::uint16_t adr) {
  if(debugger_.shouldBrake(0)) {
    std::cout << "CALL " << memoryController_.decodeValue(a) << std::endl;
    debugger_.debugConsole(0);
  }
    stack_.push(adr + 2);
    return memoryController_.readValue(a);
}
std::int32_t VirtualCPU::ret() {
  if(debugger_.shouldBrake(0)) {
    std::cout << "RET " << std::endl;
    debugger_.debugConsole(0);
  }

  if(stack_.empty()) {
    halt();
  }
    std::uint16_t ret_adr = stack_.top();
    stack_.pop();
    return memoryController_.readValue(ret_adr);
}

std::int32_t VirtualCPU::out(std::uint16_t a) {
    std::cout << static_cast<char>(memoryController_.readValue(a));
    return 2;
}

std::int32_t VirtualCPU::in(std::uint16_t a) {
  //std::cout << " IN " <<std::endl;
    char c;
    c = fgetc(stdin);
  memoryController_.accessAtAddress(a) = (std::uint16_t) c;
    return 2;
}
std::int32_t VirtualCPU::noop() {
  if(debugger_.shouldBrake(0)) {
    std::cout << "NOOP " << std::endl;
    debugger_.debugConsole(0);
  }
    return 1;
}


