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

#include <fstream>

#include "SDL2/SDL.h"

int main(int argc, const char * argv[]) {
  std::ifstream game_pak(argv[1], std::ios::binary);

  std::cout << game_pak.is_open() << std::endl;

  SDL_Surface * surface;

  SDL_Window * window;

  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("…", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 144, 0);

  surface = SDL_GetWindowSurface(window);

  SDL_UpdateWindowSurface(window);

  SDL_Delay(2000);

  SDL_DestroyWindow(window);

  SDL_Quit();
}
