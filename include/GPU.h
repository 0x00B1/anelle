#ifndef GAME_BOY_GPU_H

#define GAME_BOY_GPU_H

#include "OAM.h"

class GPU {
public:
  std::vector<OAM> OAM;
  
  std::vector<std::uint16_t> VRAM;
};

#endif
