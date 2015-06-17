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

#ifndef YOKOI_MMU_H

#define YOKOI_MMU_H

#include <iostream>
#include <map>
#include <vector>

#include "GPU.h";
#include "Time.h"

class MMU {
  std::vector<std::uint16_t> BIOS = {
    0x0031, 0x00FE, 0x00FF, 0x00AF, 0x0021, 0x00FF, 0x009F, 0x0032,
    0x00CB, 0x007C, 0x0020, 0x00FB, 0x0021, 0x0026, 0x00FF, 0x000E,
    0x0011, 0x003E, 0x0080, 0x0032, 0x00E2, 0x000C, 0x003E, 0x00F3,
    0x00E2, 0x0032, 0x003E, 0x0077, 0x0077, 0x003E, 0x00FC, 0x00E0,
    0x0047, 0x0011, 0x0004, 0x0001, 0x0021, 0x0010, 0x0080, 0x001A,
    0x00CD, 0x0095, 0x0000, 0x00CD, 0x0096, 0x0000, 0x0013, 0x007B,
    0x00FE, 0x0034, 0x0020, 0x00F3, 0x0011, 0x00D8, 0x0000, 0x0006,
    0x0008, 0x001A, 0x0013, 0x0022, 0x0023, 0x0005, 0x0020, 0x00F9,
    0x003E, 0x0019, 0x00EA, 0x0010, 0x0099, 0x0021, 0x002F, 0x0099,
    0x000E, 0x000C, 0x003D, 0x0028, 0x0008, 0x0032, 0x000D, 0x0020,
    0x00F9, 0x002E, 0x000F, 0x0018, 0x00F3, 0x0067, 0x003E, 0x0064,
    0x0057, 0x00E0, 0x0042, 0x003E, 0x0091, 0x00E0, 0x0040, 0x0004,
    0x001E, 0x0002, 0x000E, 0x000C, 0x00F0, 0x0044, 0x00FE, 0x0090,
    0x0020, 0x00FA, 0x000D, 0x0020, 0x00F7, 0x001D, 0x0020, 0x00F2,
    0x000E, 0x0013, 0x0024, 0x007C, 0x001E, 0x0083, 0x00FE, 0x0062,
    0x0028, 0x0006, 0x001E, 0x00C1, 0x00FE, 0x0064, 0x0020, 0x0006,
    0x007B, 0x00E2, 0x000C, 0x003E, 0x0087, 0x00F2, 0x00F0, 0x0042,
    0x0090, 0x00E0, 0x0042, 0x0015, 0x0020, 0x00D2, 0x0005, 0x0020,
    0x004F, 0x0016, 0x0020, 0x0018, 0x00CB, 0x004F, 0x0006, 0x0004,
    0x00C5, 0x00CB, 0x0011, 0x0017, 0x00C1, 0x00CB, 0x0011, 0x0017,
    0x0005, 0x0020, 0x00F5, 0x0022, 0x0023, 0x0022, 0x0023, 0x00C9,
    0x00CE, 0x00ED, 0x0066, 0x0066, 0x00CC, 0x000D, 0x0000, 0x000B,
    0x0003, 0x0073, 0x0000, 0x0083, 0x0000, 0x000C, 0x0000, 0x000D,
    0x0000, 0x0008, 0x0011, 0x001F, 0x0088, 0x0089, 0x0000, 0x000E,
    0x00DC, 0x00CC, 0x006E, 0x00E6, 0x00DD, 0x00DD, 0x00D9, 0x0099,
    0x00BB, 0x00BB, 0x0067, 0x0063, 0x006E, 0x000E, 0x00EC, 0x00CC,
    0x00DD, 0x00DC, 0x0099, 0x009F, 0x00BB, 0x00B9, 0x0033, 0x003E,
    0x003c, 0x0042, 0x00B9, 0x00A5, 0x00B9, 0x00A5, 0x0042, 0x004C,
    0x0021, 0x0004, 0x0001, 0x0011, 0x00A8, 0x0000, 0x001A, 0x0013,
    0x00BE, 0x0020, 0x00FE, 0x0023, 0x007D, 0x00FE, 0x0034, 0x0020,
    0x00F5, 0x0006, 0x0019, 0x0078, 0x0086, 0x0023, 0x0005, 0x0020,
    0x00FB, 0x0086, 0x0020, 0x00FE, 0x003E, 0x0001, 0x00E0, 0x0050
  };
  
  std::vector<std::uint16_t> ERAM;
  std::vector<std::uint16_t> WRAM;
  std::vector<std::uint16_t> ZRAM;

  std::vector<std::uint16_t> ROM;
public:
  MMU(CPU processor, GPU graphics, Time t):
    processor(processor), graphics(graphics), t(t) {};

  std::uint16_t IF;

  CPU processor;

  GPU graphics;

  Time t;

  bool mapped = true;

  std::uint16_t read_byte(std::uint16_t address) {
    switch (address & 0xF000) {
      case 0x0000:
        if (mapped) {
          if (address < 0x0100) {
            return BIOS[address];
          }
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
        return WRAM[address & 0x1FFF];
      case 0xC000:
      case 0xD000:
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
            if ((address & 0x00FF) < 0x00A0) {
              return graphics.OAM[address & 0x00FF];
            } else {
              return 0;
            }
          case 0x0F00:
            if (address > 0xFF7F) {
              return ZRAM[address & 0x007F];
            } else {
              switch (address & 0x00F0) {
                default:
                  break;
              }
            }
          default:
            break;
        }
      default:
        break;
    }
    
    return 0;
  }
  
  std::uint16_t read_word(uint16_t address) {
    return read_byte(address) + (read_byte((uint16_t) (address + 1)) << 8);
  }
  
  void write_byte(std::uint16_t address, std::uint8_t byte) {
    switch (address & 0xF000) {
      case 0x0000:
        if (mapped && address < 0x0100) {
          return;
        }
      case 0x1000:
      case 0x2000:
      case 0x3000:
        break;
      case 0x4000:
      case 0x5000:
      case 0x6000:
      case 0x7000:
        break;
      case 0x8000:
      case 0x9000:
        break;
      case 0xA000:
      case 0xB000:
        ERAM[address & 0x1FFF] = byte;
        
        break;
      case 0xC000:
      case 0xD000:
      case 0xE000:
        WRAM[address & 0x1FFF] = byte;
        
        break;
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
            
            break;
          case 0x0E00:
            if ((address & 0x00FF) < 0x00A0) {
              
            }
            
            break;
          case 0x0F00:
            if (address > 0xFF7F) {
              ZRAM[address & 0x007F] = byte;
            } else {
              switch (address & 0x00F0) {
                default:
                  break;
              }
            }
            
            break;
            default:
                break;
        }
        
        break;
      default:
        break;
    }
  }
  
  void write_word(std::uint16_t address, std::uint16_t word) {
    write_byte(address, (uint8_t) (word & 255));
    
    write_byte((uint16_t) (address + 1), (uint8_t) (word >> 8));
  }
};

#endif
