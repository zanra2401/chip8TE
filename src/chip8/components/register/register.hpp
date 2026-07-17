#pragma once
#include <cstdint>
#include <iostream>


class Register {
  private:
    uint8_t V[16];
    uint16_t I;
  public:
    uint8_t get_v_register(unsigned short location);
    void set_v_register(unsigned short location, uint8_t data);
    uint16_t get_i_register();
    void set_i_register(uint16_t data);
    void clear_registers();
};
