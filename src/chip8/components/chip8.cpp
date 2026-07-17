#include "./chip8.hpp"


Chip8TE::Chip8TE() {
  graphic.clear_disp();
  memory.clear_stack();
  register_c.clear_register();
  memory.clear_memory();
  memory.load_font();
}

void Chip8TE::load_program(const char *file_name) {
  program_loader.load_from_file(file_name);
  bytes = program_loader.get_bytes();
}

void Chip8TE::emulate_cycle() {
  opcode = memory[pc] << 8 | memory[pc + 1];

}

void opcode_handler(uint16_t opcode) {
  switch (opcode & 0xF000) {
    case 
  }
}
