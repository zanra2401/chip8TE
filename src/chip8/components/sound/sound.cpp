#include "sound.hpp"
#include <iostream>

void SoundTimer::set_timer(uint8_t time) {
    this->time = time;
}

uint8_t SoundTimer::get_time() {
    return this->time;
}

void SoundTimer::count_down() {
    if (this->time > 0) {
        // Mainkan suara 'beep' (tergantung implementasi platform, contoh menggunakan bell character)
        if (this->time == 1) {
            std::cout << '\a' << std::flush;
        }
        this->time--;
    }
}
