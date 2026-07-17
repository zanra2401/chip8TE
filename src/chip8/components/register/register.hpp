#pragma once
#include <cstdint>
#include <iostream>


class Register {
  private:
    uint8_t V[16];
    short I[1];
  public:
    uint8_t get_v_register(unsigned short location);
    void set_v_register(unsigned short location, uint8_t data);
    void clear_registers();
};
