#pragma once
#include <cstdint>
#include "../../../rendering_engine/tEngine.hpp"

class Graphic {
  private:
    TEngine engine;
  public:
    Graphic();
    void disp_clear();
};
