#pragma once
#include "./graphic/graphic.hpp"
#include "./memory/memory.hpp"
#include "./input/input.hpp"
#include "./register/register.hpp"
#include "./sound/sound.hpp"
#include "./timers/timer.hpp"
#include "./opcode/opcode.hpp"
#include "../program_loader/program_loader.hpp"


class Chip8TE {
  private:
    uint16_t pc = 0x200;
    uint16_t current_opcode = 0;
    Memory memory;
    Register register_c;
    PLoader program_loader;
    Opcode opcode_decoder;
    uint8_t *rom_bytes;
  public:
    Graphic graphic;
    Chip8TE();
    void load_program(const char *file_name);
    void emulate_cycle();
    void opcode_handler(uint16_t opcode);

};
