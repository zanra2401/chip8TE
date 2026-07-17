#pragma once
#include <cstdint>


class Input {
  private:
    char keyboard[0xF] = {'0', '1', '2', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  public:
    void process();
};
