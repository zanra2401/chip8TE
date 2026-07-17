#include "tEngine.hpp"

TEngine::TEngine(Vector2d_s screen_size, Vector2d_s scale) : frame_buffer(screen_size) {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios raw = oldt;
    raw.c_lflag &= ~ECHO;
    raw.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);    
    this->screen_size = screen_size; 
    this->scale = scale;
    set_center_pos();
    set_start_index();
    hide_cursor();
}

void TEngine::set_scale(Vector2d_s new_scale) {
    this->scale = new_scale;
    set_start_index();
    clear_screen();
}


void TEngine::clear_screen() {
  frame_buffer.clear_frame_buffer();
  draw_frame_buffer();
}

void TEngine::set_center_pos() {
    center_pos.x = (short) (w.ws_col / 2);
    center_pos.y = (short) (w.ws_row / 2); // FIX: Menggunakan '=' bukan '-'
}

void TEngine::set_start_index() {
    short total_width = screen_size.x * scale.x;
    short total_height = screen_size.y * scale.y;

    if (total_width > w.ws_col || total_height > w.ws_row) {
        std::cerr << "Ukuran terminal terlalu kecil untuk layar Emulator!\n";
        std::exit(-1);
    }

    start_index.x = center_pos.x - (total_width / 2);
    start_index.y = center_pos.y - (total_height / 2);
}

void TEngine::print_pixel(Vector2d_s pos, ColorRGB_s color) {
    Vector2d_s screen_pos = to_screen_position(pos);

    for (short sy = 0; sy < scale.y; sy++) {
        // +1 karena ANSI escape code 1-indexed
        std::cout << "\033[" << (screen_pos.y + sy + 1) << ";" << (screen_pos.x + 1) << "H";
        std::cout << "\033[48;2;" << color.r << ";" << color.g << ";" << color.b << "m";
        for (short sx = 0; sx < scale.x; sx++) {
            std::cout << " ";
        }
        std::cout << "\033[0m";
    }
    std::cout << std::flush;
}

void TEngine::enter_alt() {
    std::cout << "\033[?1049h" << std::flush; // Singkirkan tanda titik dua ':' yang tidak perlu
}

void TEngine::leave_alt() {
    std::cout << "\033[?1049l" << std::flush;
}

void TEngine::hide_cursor() {
  std::cout << "\033[?25l";
}

void TEngine::show_cursor() {
  std::cout << "\033[?25h";
}

void TEngine::draw_object(Object_t object_to_draw) {
  std::string buffer = build_object_into_buffer_string(object_to_draw);
  blit(buffer);
}

void TEngine::blit(std::string &buffer) {
  std::cout << buffer << std::flush;
}

void TEngine::draw_frame_buffer() {
  Object_t object = frame_buffer.build_dirty_map();
  std::string string_buffer = build_object_into_buffer_string(object);
  blit(string_buffer);
}


std::string TEngine::build_object_into_buffer_string(Object_t &object_to_build) { 
  std::stringstream buffer;        
  ColorRGB_s color_now;
  
  for (short i = 0; i < object_to_build.size(); i++) {
    if (i == 0 || color_now != object_to_build[i].color) {
      ColorRGB_s color = object_to_build[i].color;
      buffer << "\033[48;2;" << color.r << ";" << color.g << ";" << color.b << "m";
      color_now = color;
    }
    Vector2d_s pos = to_screen_position(object_to_build[i].pos);

    for (short sy = 0; sy < scale.y; sy++) {
        // ANSI index starts from 1, so pos.y + sy + 1
        buffer << "\033[" << (pos.y + sy + 1) << ";" << (pos.x + 1) << "H";
        for (short sx = 0; sx < scale.x; sx++) {
            buffer << " ";
        }
    }
  }

  buffer << "\033[0m";

  return buffer.str();
};


Vector2d_s TEngine::get_screen_size() {
    return screen_size;
}

Vector2d_s TEngine::to_screen_position(Vector2d_s pos) {
    Vector2d_s screen_pos;
    screen_pos.x = start_index.x + (pos.x * scale.x); 
    screen_pos.y = start_index.y + (pos.y * scale.y);
    return screen_pos;
}

Vector2d_s TEngine::get_center_pos() {
    return center_pos;
}
