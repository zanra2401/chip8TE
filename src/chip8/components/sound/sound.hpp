#pragma once
#include <cstdint>


class SoundTimer {
  private:
    uint8_t time;
  public:
    void set_timer(uint8_t time);
    void count_down();
};
