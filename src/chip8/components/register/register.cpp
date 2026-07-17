#include "./register.hpp"
#include <cstdlib>

uint8_t Register::get_v_register(unsigned short location) {
  return V[location];
}

void Register::set_v_register(unsigned short location, uint8_t data) {
  if (location < 0x0 || location > 0xF) {
    std::cerr << "Error OverFlow Register" << std::endl;
    std::exit(-1);
  }
  V[location] = data;
}

void Register::clear_registers() {
  for (uint8_t i = 0x0; i <= 0xF; i++) {
    V[i] = 0x00;
  }
  I = 0x0000;
}

uint16_t Register::get_i_register() {
  return I;
}

void Register::set_i_register(uint16_t data) {
  I = data;
}
