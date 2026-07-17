#include "tEngine.hpp"

TEngine::TEngine(Vector2d_s screen_size) : frame_buffer(screen_size) {
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios raw = oldt;
    raw.c_lflag &= ~ECHO;
    raw.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);    
    this->screen_size = screen_size; // FIX: Gunakan this-> agar terisi
    set_center_pos();
    set_start_index();
    hide_cursor();
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
    // Kalibrasi screen_size.x * 2 karena 1 piksel = 2 karakter lebar
    short total_lebar_karakter = screen_size.x * 2;

    if (total_lebar_karakter > w.ws_col || screen_size.y > w.ws_row) {
        std::cerr << "Ukuran terminal terlalu kecil untuk layar Emulator!\n";
        std::exit(-1);
    }

    // Menghitung titik awal (pojok kiri atas) agar layar tepat di tengah terminal
    start_index.x = center_pos.x - (total_lebar_karakter / 2);
    start_index.y = center_pos.y - (screen_size.y / 2);
}

void TEngine::print_pixel(Vector2d_s pos, ColorRGB_s color) {
    // 1. Konversi dari koordinat lokal game ke koordinat layar terminal asli
    Vector2d_s screen_pos = to_screen_position(pos);

    // 2. Pindahkan kursor menggunakan aturan ANSI yang benar: \033[Baris(Y);Kolom(X)H
    //
    // Karena index ANSI dimulai dari 1, tambahkan +1
    std::cout << "\033[" << (screen_pos.y + 1) << ";" << (screen_pos.x + 1) << "H";

    // 3. Cetak warna background putih dengan 2 spasi sebagai 1 piksel kotak
    std::cout << "\033[1;37;47m  ";
    
    // 4. Reset warna kursor kembali normal dan flush output
    std::cout << "\033[0m" << std::flush;
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
  std::cout << buffer;
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

    buffer << "\033[" << pos.y << ";" << pos.x << "H  ";
  }

  buffer << "\033[0m";

  return buffer.str();
};


Vector2d_s TEngine::get_screen_size() {
    return screen_size;
}

Vector2d_s TEngine::to_screen_position(Vector2d_s pos) {
    Vector2d_s screen_pos;
    // X dikali 2 karena tiap koordinat X memakan 2 spasi karakter fisik
    screen_pos.x = start_index.x + (pos.x * 2); 
    screen_pos.y = start_index.y + pos.y;
    return screen_pos;
}

Vector2d_s TEngine::get_center_pos() {
    return center_pos;
}
