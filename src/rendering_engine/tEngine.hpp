#pragma once
#include "../types/typedef.hpp"
#include "../types/screen.hpp"
#include "../types/geometry.hpp"
#include "./frame_buffer.cpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sstream>

class TEngine {
  private:
    winsize w;
    Vector2d_s screen_size;
    Vector2d_s start_index;
    Vector2d_s center_pos;
    FrameBuffer frame_buffer;
    void set_center_pos();
    void set_start_index();
    void blit(std::string &buffer_to_blit);
    std::string build_object_into_buffer_string(Object_t &object_to_build);

  public:
    TEngine(Vector2d_s screen_size);
    void clear_screen();
    void print_pixel(Vector2d_s pos, ColorRGB_s color = ColorRGB_s(255,255,255));
    void enter_alt();
    void leave_alt();
    void draw_object(Object_t object_to_draw);
    void hide_cursor();
    void show_cursor();
    void draw_frame_buffer();

    Vector2d_s get_screen_size();
    Vector2d_s to_screen_position(Vector2d_s pos);
    Vector2d_s get_center_pos();
};
