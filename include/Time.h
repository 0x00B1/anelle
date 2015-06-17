#ifndef YOKOI_TIME_H

#define YOKOI_TIME_H

#include <cstdint>
#include <map>
#include <string>

#include "CPU.h"
#include "MMU.h"

class Time {
public:
  class Clock {
  public:
    std::uint16_t div, main, sub;
  };

  CPU processor;
  MMU memory;

  Clock clock;

  std::uint16_t DIV, TAC, TIMA, TMA;

  Time operator ++ () {
    Time time(*this);

    std::uint16_t temporary = clock.main;

    clock.sub = processor.instruction_execution.M;

    if (clock.sub > 3) {
      clock.main++;

      clock.sub = (uint16_t) (clock.sub - 4);

      clock.div++;

      if (clock.div == 16) {
        clock.div = 0;

        DIV++;

        DIV &= 255;
      }
    }

    if (TAC & 4) {
      switch (TAC & 3) {
        case 0:
          if (clock.main >= 64) {
            step();
          }

          break;
        case 1:
          if (clock.main >= 1) {
            step();
          }

          break;
        case 2:
          if (clock.main >= 4) {
            step();
          }

          break;
        case 3:
          if (clock.main >= 16) {
            step();
          }

          break;
        default:
          break;
      }
    }

    return time;
  };

  std::uint16_t read(std::uint16_t address) {
    switch (address) {
      case 0xFF04:
        return DIV;
      case 0xFF05:
        return TIMA;
      case 0xFF06:
        return TMA;
      case 0xFF07:
        return TAC;
      default:
        return 0;
    }
  }

  void step(void) {
    TIMA++;

    clock.main = 0;

    if (TIMA > 255) {
      TIMA = TMA;

      memory.IF |= 4;
    }
  }

  void write(std::uint16_t address, std::uint16_t byte) {
    switch (address) {
      case 0xFF04:
        DIV = 0;

        break;
      case 0xFF05:
        TIMA = byte;

        break;
      case 0xFF06:
        TMA = byte;

        break;
      case 0xFF07:
        TAC = (uint16_t) (byte & 7);

        break;
      default:
        break;
    }
  }
};

#endif