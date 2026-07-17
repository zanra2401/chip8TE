#pragma once
#include <cstdint>
#include "../../../rendering_engine/tEngine.hpp"

class Graphic {
  public:
    TEngine engine;
    Graphic();
    void disp_clear();
    bool draw_sprite(uint8_t x, uint8_t y, uint8_t* sprite, uint8_t height);
    void render();
};
