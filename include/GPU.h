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

#ifndef YOKOI_GPU_H

#define YOKOI_GPU_H

#include <cstdint>
#include <vector>

#include "OAM.h"

class GPU {
public:
  std::vector<OAM> OAM;

  std::vector<std::uint16_t> object_data;
  std::vector<std::uint16_t> object_data_sorted;

  std::map<const std::string, std::vector<std::uint16_t>> palette = {
    { "bg", {} }, { "obj0", {} }, { "obj1", {} }
  };

  std::vector<std::uint16_t> registers;
  std::vector<std::uint16_t> scan_row;
  std::vector<std::uint16_t> sheet;
  std::vector<std::uint16_t> tilemap;
  std::vector<std::uint16_t> VRAM;

  std::uint16_t bgmapbase = 0x1800;
  std::uint16_t bgon = 0;
  std::uint16_t bgtilebase = 0x0000;
  std::uint16_t curline = 0;
  std::uint16_t curscan = 0;
  std::uint16_t ints = 0;
  std::uint16_t lcdon = 0;
  std::uint16_t linemode = 0;
  std::uint16_t modeclocks = 0;
  std::uint16_t objon = 0;
  std::uint16_t objsize = 0;
  std::uint16_t raster = 0;
  std::uint16_t winon = 0;
  std::uint16_t wintilebase = 0x1800;
  std::uint16_t xscrl = 0;
  std::uint16_t yscrl = 0;

  void reset(void) {}

  void update_sprite(std::uint16_t address) {
    std::uint16_t saddr = address;

    if (address & 1) {
      saddr--;

      address--;
    }

    std::uint16_t tile = (uint16_t) ((address >> 4) & 511);

    std::uint16_t y = (uint16_t) ((address >> 1) & 7);

    std::uint16_t sx;

    for (int j = 0; j < 8; ++j) {
      sx = (uint16_t) (1 << (7 - j));

      // tilemap[tile][y][x]
      // (VRAM[saddr] & sx ? 1 : 0) | (VRAM[saddr + 1] & sx) ? 2 : 0;
    }
  }

  void update_OAM(std::uint16_t address, std::uint16_t e) {
    address = (uint16_t) (address - 0xFE00);

    std::uint16_t object = address >> 2;

    if (object) {
      switch (address & 3) {
        case 0:
        case 1:
        case 2:
        case 3:
        default:
          break;
      }
    }
  }

  void read(std::uint16_t address) {

  }

  std::uint16_t write(std::uint16_t byte, std::uint16_t address) {
    std::uint16_t gaddr = (uint16_t) (address - 0xFF40);

    switch (gaddr) {
      case 0:
      case 1:
        return (uint16_t) (curline == raster ? 4 : 0) | linemode;
      case 2:
        return yscrl;
      case 3:
        return xscrl;
      case 4:
        return curline;
      case 5:
        return raster;
      default:
        break;
    }
  }
};

#endif
