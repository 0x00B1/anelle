/*
 * The MIT License (MIT)
 *
 * Copyright © 2015 Allen Goodman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS,” WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef YOKOI_CPU_H

#define YOKOI_CPU_H

#include <cstdint>
#include <map>
#include <string>

namespace Yokoi {
  class CPU {
  public:
    std::map<const std::string, std::uint16_t> registers = {
      /*
       * MAIN REGISTERS
       */

      { "A",  0 }, { "F",  0 }, // AF (ACCUMULATOR AND FLAGS)
      { "B",  0 }, { "C",  0 }, // BC
      { "D",  0 }, { "E",  0 }, // DE
      { "H",  0 }, { "L",  0 }, // HL (INDIRECT ADDRESS)

      /*
       * ALTERNATE REGISTERS
       */

      { "A′", 0 }, { "F′", 0 }, // AF′ (ACCUMULATOR AND FLAGS)
      { "B′", 0 }, { "C′", 0 }, // BC′
      { "D′", 0 }, { "E′", 0 }, // DE′
      { "H′", 0 }, { "L′", 0 }, // HL′ (INDIRECT ADDRESS)

      /*
       * INDEX REGISTERS
       */

      { "IX", 0 },              // INDEX X
      { "IY", 0 },              // INDEX Y
      { "SP", 0 },              // STACK POINTER

      /*
       * OTHER REGISTERS
       */

      { "I",  0 },              // INTERRUPT VECTOR
      { "R",  0 },              // REFRESH COUNTER

      /*
       * PROGRAM COUNTER
       */

      { "PC", 0 },              // PROGRAM COUNTER
    };
  };
}

#endif
