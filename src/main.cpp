#include <fstream>
#include <iostream>

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
