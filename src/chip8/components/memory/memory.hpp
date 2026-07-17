#pragma once
#include <cstdint>
#include <iostream>



class Memory {
  private:
    uint8_t memory[4096];
    unsigned short offset_stack = 0x000;
    unsigned short start_stack = 0xEA0;
    unsigned short end_stack = 0xEFF;
    unsigned short display_refresh_start = 0xF00;
    unsigned short display_refresh_end = 0xFFF;
    unsigned short start_font = 0x000;
    unsigned short end_font = 0x1FF;
  

  public:
    uint8_t* get_data_from_memory(uint16_t location);
    void load_bytes(uint8_t *bytes, int file_size); 
    void push_to_stack(uint8_t data);
    uint8_t pop_from_stack();
    void clear_memory();
    void clear_stack();
    void load_font();
};
