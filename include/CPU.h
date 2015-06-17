#ifndef YOKOI_CPU_H

#define YOKOI_CPU_H

#include "MMU.h"

class CPU {
public:
  class Time {
  public:
    std::uint16_t M;
    std::uint16_t T;
  };
  
  MMU memory;
  
  Time time;
  
  Time instruction_execution;
  
  bool halted = false;
  
  enum Status {
    S = 0x0000, // SIGN
    Z = 0x0080, // ZERO
    H = 0x0020, // HALF-CARRY
    P = 0x0000, // PARITY OR OVERFLOW
    N = 0x0040, // ADD OR SUBTRACT
    C = 0x0010, // CARRY
  };
  
  std::map<const std::string, std::uint16_t> registers = {
    /*
     * MAIN REGISTERS
     */
    { "A", 0 },  { "F", 0 },  // AF (ACCUMULATOR AND FLAGS)
    { "B", 0 },  { "C", 0 },  // BC
    { "D", 0 },  { "E", 0 },  // DE
    { "H", 0 },  { "L", 0 },  // HL (INDIRECT ADDRESS)
    
    /*
     * INDEX REGISTERS
     */
    { "IX", 0 },              // INDEX X
    { "IY", 0 },              // INDEX Y
    { "SP", 0 },              // STACK POINTER
    
    /*
     * OTHER REGISTERS
     */
    { "I", 0 },               // INTERRUPT VECTOR
    { "R", 0 },               // REFRESH COUNTER
    
    /*
     * PROGRAM COUNTER
     */
    { "PC", 0 },              // PROGRAM COUNTER
  };
  
  void execute(std::uint8_t instruction) {
    switch (instruction) {
      case 0x0000:
        NOP();
      default:
        break;
    }
  }
  
  void execute(void) {
    registers["R"] = (unsigned short) ((registers["R"] + 1) & 127);
    
    std::function<void(void)> instruction = instructions["POP"];
    
    instruction();
    
    registers["PC"] &= 65535;
    
    time.M = time.M + instruction_execution.M;
    time.T = time.T + instruction_execution.T;
    
    if (memory.mapped && registers["PC"] == 0x0100) {
      memory.mapped = false;
    }
  }
  
  void reset(void) {
    std::vector<const std::string> K;
    
    std::transform(registers.begin(), registers.end(), std::back_inserter(K),
                   [] (std::pair<const std::string, std::uint16_t> KV) {
                     return KV.first;
                   });
    
    for (const std::string k: K) {
      registers[k] = 0;
    }
    
    time.M = 0;
    time.T = 0;
    
    instruction_execution.M = 0;
    instruction_execution.T = 0;
  }
  
  void HALT(void) {
    halted = true;
    
    instruction_execution.M = 1;
    instruction_execution.T = 4;
  }
  
  void LD(void) {
    std::uint16_t address = memory.read_word(registers["PC"]);
    
    registers["PC"] = (unsigned short) (registers["PC"] + 2);
    
    registers["A"] = memory.read_byte(address);
    
    instruction_execution.M =  4;
    instruction_execution.T = 16;
  }
  
  void NOP(void) {
    instruction_execution.M = 1;
    instruction_execution.T = 4;
  }
  
  void POP(void) {
    registers["L"] = memory.read_byte(registers["SP"]);
    
    registers["SP"]++;
    
    registers["H"] = memory.read_byte(registers["SP"]);
    
    registers["SP"]++;
    
    instruction_execution.M =  3;
    instruction_execution.T = 12;
  }
  
  void PUSH(void) {
    registers["SP"]--;
    
    memory.write_byte(registers["SP"], (uint8_t) registers["B"]);
    
    registers["SP"]--;
    
    memory.write_byte(registers["SP"], (uint8_t) registers["C"]);
    
    instruction_execution.M =  3;
    instruction_execution.T = 12;
  }
  
  std::map<std::string, std::function<void(void)>> instructions = {
    {
      "HALT",
      std::bind(&CPU::HALT, this)
    },
    {
      "LD",
      std::bind(&CPU::LD, this)
    },
    {
      "NOP",
      std::bind(&CPU::NOP, this)
    },
    {
      "POP",
      std::bind(&CPU::POP, this)
    },
    {
      "PUSH",
      std::bind(&CPU::PUSH, this)
    },
  };
};

#endif
