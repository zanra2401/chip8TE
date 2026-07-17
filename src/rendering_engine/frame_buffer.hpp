#include <iostream>
#include "../types/screen.hpp"
#include "../types/geometry.hpp"
#include <cstdint>


class FrameBuffer {
  public:
    FrameBuffer(Vector2d_s screen_size) {
      this->buffer_size = screen_size;
      this->frame_buffer = new ColorRGB_s*[screen_size.y];
      for (unsigned short y = 0; y < screen_size.y; y++) {
          frame_buffer[y] = new ColorRGB_s[screen_size.x];
      }
    }

    ~FrameBuffer() {
      for (uint8_t y = 0; y < buffer_size.y; y++) {
        delete[] frame_buffer[y];
      }
      delete[] frame_buffer;
    }

    void clear_frame_buffer() {
        ColorRGB_s hitam = {0, 0, 0}; // Sesuaikan dengan struct warnamu
        for (int y = 0; y < buffer_size.y; y++) {
            for (int x = 0; x < buffer_size.x; x++) {
                frame_buffer[y][x] = hitam;
                dirty_map.push_back(Vector2d_s((short)x, (short)y));
            }
        }
    }

    void set_pixel(Vector2d_s pos, ColorRGB_s color) {
      frame_buffer[pos.y][pos.x] = color;
      dirty_map.push_back(pos);
    }

    bool xor_pixel(Vector2d_s pos, ColorRGB_s on_color) {
        ColorRGB_s black = {0, 0, 0};
        ColorRGB_s current = frame_buffer[pos.y][pos.x];
        bool erased = false;
        
        if (!(current == black)) { // Turn off
            frame_buffer[pos.y][pos.x] = black;
            erased = true;
        } else { // Turn on
            frame_buffer[pos.y][pos.x] = on_color;
        }
        
        dirty_map.push_back(pos);
        return erased;
    }

    ColorRGB_s** get_frame_buffer() {
      return this->frame_buffer;
    }

    Object_t build_dirty_map() {
        Object_t object;
        
        // Gunakan range-based for loop, jauh lebih cepat dan bersih
        for (const auto& local_pos : dirty_map) {
            ColorRGB_s pixel_color = frame_buffer[local_pos.y][local_pos.x];
            
            Pixel_s pixel;
            pixel.pos = local_pos;
            pixel.color = pixel_color;
            
            object.push_back(pixel);
        }
        
        // Setelah semua dibaca, kosongkan antrean sekaligus tanpa geser memori
        dirty_map.clear(); 
        
        return object; 
    }
  private:
    ColorRGB_s **frame_buffer;
    Vector2d_s buffer_size;
    std::vector<Vector2d_s> dirty_map;
};
