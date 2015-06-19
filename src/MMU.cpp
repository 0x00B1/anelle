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

#include "MMU.h"

namespace Yokoi {
  std::uint8_t MMU::read_uint8_t(std::uint16_t address) {
    switch (address & 0xF000) {
      case 0x0000:
        if (mapped && address < 0x0100) {
          return BIOS[address];
        } else if (mapped && CPU.registers["PC"] == 0x0100) {
          mapped = false;

          return ROM[address];
        } else {
          return ROM[address];
        }
      case 0x1000:
      case 0x2000:
      case 0x3000:
        return ROM[address];
      case 0x4000:
      case 0x5000:
      case 0x6000:
      case 0x7000:
        return ROM[address];
      case 0x8000:
      case 0x9000:
      case 0xA000:
      case 0xB000:
        return ERAM[address & 0x1FFF];
      case 0xC000:
      case 0xD000:
        return WRAM[address & 0x1FFF];
      case 0xE000:
        return WRAM[address & 0x1FFF];
      case 0xF000:
        switch (address & 0x0F00) {
          case 0x0000:
          case 0x0100:
          case 0x0200:
          case 0x0300:
          case 0x0400:
          case 0x0500:
          case 0x0600:
          case 0x0700:
          case 0x0800:
          case 0x0900:
          case 0x0A00:
          case 0x0B00:
          case 0x0C00:
          case 0x0D00:
            return WRAM[address & 0x1FFF];
          case 0x0E00:
          case 0x0F00:
            if (address == 0xFFFF) {
              return 1;
            } else if (address >= 0xFF7F) {
              return ZRAM[address & 0x07F];
            }

            switch (address & 0x00F0) {
              case 0x0000:
              case 0x0010:
              case 0x0020:
              case 0x0030:
              case 0x0040:
              case 0x0050:
              case 0x0060:
              case 0x0070:
              case 0x0080:
              case 0x0090:
              case 0x00A0:
              case 0x00B0:
              case 0x00C0:
              case 0x00D0:
              case 0x00E0:
              case 0x00F0:
              default:
                return 0;
            }
          default:
            return 0;
        }
      default:
        return 0;
    }
  }

  std::uint16_t MMU::read_uint16_t(std::uint16_t address) {
    return read_uint8_t(address) + (read_uint8_t((uint16_t) (address + 1)) << 8);
  }

  void MMU::write_uint8_t(std::uint16_t address, std::uint8_t byte) {
    switch (address & 0xF000) {
      case 0x0000:
      case 0x1000:
      case 0x2000:
      case 0x3000:
      case 0x4000:
      case 0x5000:
      case 0x6000:
      case 0x7000:
      case 0x8000:
      case 0x9000:
      case 0xA000:
      case 0xB000:
        ERAM[address & 0x1FFF] = byte;
      case 0xC000:
      case 0xD000:
      case 0xE000:
        WRAM[address & 0x1FFF] = byte;
      case 0xF000:
        switch (address & 0x0F00) {
          case 0x0000:
          case 0x0100:
          case 0x0200:
          case 0x0300:
          case 0x0400:
          case 0x0500:
          case 0x0600:
          case 0x0700:
          case 0x0800:
          case 0x0900:
          case 0x0A00:
          case 0x0B00:
          case 0x0C00:
          case 0x0D00:
            WRAM[address & 0x1FFF] = byte;
          case 0x0E00:
          case 0x0F00:
            if (address >= 0xFF7F) {
              ZRAM[address & 0x007F] = byte;
            }

            switch (address & 0x00F0) {
              case 0x0000:
              case 0x0010:
              case 0x0020:
              case 0x0030:
              case 0x0040:
              case 0x0050:
              case 0x0060:
              case 0x0070:
              case 0x0080:
              case 0x0090:
              case 0x00A0:
              case 0x00B0:
              case 0x00C0:
              case 0x00D0:
              case 0x00E0:
              case 0x00F0:
              default:
                break;
            }
          default:
            break;
        }
      default:
        break;
    }
  }

  void MMU::write_uint16_t(std::uint16_t address, std::uint16_t byte) {
    write_uint8_t(address, (uint8_t) (byte & 255));

    write_uint8_t((uint16_t) (address + 1), (uint8_t) (byte >> 8));
  }
}
