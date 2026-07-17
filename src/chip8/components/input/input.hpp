#pragma once
#include <cstdint>


class Input {
  private:
    char keyboard[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    bool key_state[16] = {false};
  public:
    void process();
    bool is_key_pressed(uint8_t key);
};
