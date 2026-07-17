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
    Graphic graphic = Graphic();
    Memory memory = Memory();
    Register register_c = Register();
    PLoader program_loader = PLoader();
    Opcode opcode_decoder = Opcode();
    uint8_t *rom_bytes;
  public:
    Chip8TE();
    void load_program(const char *file_name);
    void emulate_cycle();
    void opcode_handler(uint16_t opcode);

};
