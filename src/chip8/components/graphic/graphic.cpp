#include "./graphic.hpp" 


Graphic::Graphic() {
  engine = TEngine({64, 32});
}

void Graphic::disp_clear() {
  engine.clear_screen();
}

bool Graphic::draw_sprite(uint8_t x, uint8_t y, uint8_t* sprite, uint8_t height) {
    bool collision = false;
    ColorRGB_s white(255, 255, 255);
    
    // CHIP-8 sprite loop
    for (uint8_t row = 0; row < height; row++) {
        uint8_t sprite_byte = sprite[row];
        for (uint8_t col = 0; col < 8; col++) {
            // Check if the current bit in the sprite is 1
            if ((sprite_byte & (0x80 >> col)) != 0) {
                // Wrap around horizontally and vertically
                uint8_t screen_x = (x + col) % 64; // Sesuaikan dengan resolusi
                uint8_t screen_y = (y + row) % 32;
                
                if (engine.frame_buffer.xor_pixel(Vector2d_s(screen_x, screen_y), white)) {
                    collision = true;
                }
            }
        }
    }
    
    return collision;
}

void Graphic::render() {
    engine.draw_frame_buffer();
}
