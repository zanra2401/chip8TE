#pragma once
#include <cstdint>


class Timer {
  private:
    uint8_t time;
  public:
    void set_timer(uint8_t time);
    uint8_t get_time();
    void count_down();
};
