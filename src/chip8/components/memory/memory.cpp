#include "memory.hpp"

Memory::Memory() {

}


uint8_t Memory::get_data_from_memory(uint16_t location) {
  if (location >= 4096) {
    std::cerr << "Memory Overflow Error" << std::endl;
    std::exit(-1);
  }
  return memory[location];
}

uint8_t* Memory::get_memory_ptr(uint16_t location) {
  if (location >= 4096) {
    std::cerr << "Memory Overflow Error" << std::endl;
    std::exit(-1);
  }
  return &memory[location];
}


void Memory::load_data(uint8_t *bytes, int file_size) {
  if (file_size > (4096 - 0x200)) {
    std::cerr << "ROM Size is too large for Memory!" << std::endl;
    std::exit(-1);
  }

  int address = 0x200;

  for (unsigned short byte = 0; byte < file_size; byte++) {
    memory[address] = bytes[byte];
    address++;
  }
}

void Memory::push_to_stack(uint8_t data) {
  if (offset_stack > end_stack) {
    std::cerr << "Error Stack OverFlow" << std::endl;
  }
  memory[offset_stack] = data;
  offset_stack += 1;
}


uint8_t Memory::pop_from_stack() {
  if (offset_stack - 1 < start_stack) {
    std::cerr << "Error Stack OverFlow" << std::endl;
  }
  offset_stack--;
  uint8_t data = memory[offset_stack];
  memory[offset_stack] = 0x00;
  return data;
}


void Memory::clear_stack() {
  for (int i = 0x200; i <= 0x400; i++) {
    memory[i] = 0x00;
  }
}


void Memory::clear_memory() {
  for (int i = start_stack; i <= end_stack; i++) {
    memory[i] = 0x00;
  }
}

void Memory::load_font() {
  constexpr uint8_t chip8_fontset[80] = {
    // 0
    0xF0, 0x90, 0x90, 0x90, 0xF0,
    // 1
    0x20, 0x60, 0x20, 0x20, 0x70,
    // 2
    0xF0, 0x10, 0xF0, 0x80, 0xF0,
    // 3
    0xF0, 0x10, 0xF0, 0x10, 0xF0,
    // 4
    0x90, 0x90, 0xF0, 0x10, 0x10,
    // 5
    0xF0, 0x80, 0xF0, 0x10, 0xF0,
    // 6
    0xF0, 0x80, 0xF0, 0x90, 0xF0,
    // 7
    0xF0, 0x10, 0x20, 0x40, 0x40,
    // 8
    0xF0, 0x90, 0xF0, 0x90, 0xF0,
    // 9
    0xF0, 0x90, 0xF0, 0x10, 0xF0,
    // A
    0xF0, 0x90, 0xF0, 0x90, 0x90,
    // B
    0xE0, 0x90, 0xE0, 0x90, 0xE0,
    // C
    0xF0, 0x80, 0x80, 0x80, 0xF0,
    // D
    0xE0, 0x90, 0x90, 0x90, 0xE0,
    // E
    0xF0, 0x80, 0xF0, 0x80, 0xF0,
    // F
    0xF0, 0x80, 0xF0, 0x80, 0x80
  };
  
  for (uint8_t i = 0; i < 80; i++) {
    memory[start_font + i] = chip8_fontset[i];
  }
}








