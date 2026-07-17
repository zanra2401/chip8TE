#pragma once
#include <fstream>
#include <cstdint>
#include <cstdio>
#include <iostream>

class PLoader {
  private :
    int file_size = 0;
    uint8_t *bytes = nullptr;
  public:
    PLoader();
    ~PLoader();
    void load_from_file(const char *file_name);
    void ddebug();
    int get_file_size();
    uint8_t *get_bytes();
};
