#include <fstream>
#include <iostream>

#include "SDL2/SDL.h"

int main(int argc, const char * argv[]) {
    std::ifstream game_pak(argv[1], std::ios::binary);

    std::cout << game_pak.is_open() << std::endl;
}
