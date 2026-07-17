#pragma once
#include "./graphic/graphic.hpp"
#include "./memory/memory.hpp"
#include "./input/input.hpp"
#include "./register/register.hpp"
#include "./sound/sound.hpp"
#include "./timers/timer.hpp"
#include "../program_loader/program_loader.hpp"


class Chip8TE {
  private:
    unsigned short = 0x200;
    unsigned short = 0;
    Graphic graphic = Graphic();
    Memory memory = Memory();
    Register register_c = Regiter();
    PLoader program_loader = PLoader();
    uint8_t *test;
  public:
    Chip8TE();
    void load_program(const char *file_name);
    void emulte_cycle();

}
