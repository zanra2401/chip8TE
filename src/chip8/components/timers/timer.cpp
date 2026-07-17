#include "timer.hpp"

void Timer::set_timer(uint8_t time) {
    this->time = time;
}

uint8_t Timer::get_time() {
    return this->time;
}

void Timer::count_down() {
    if (this->time > 0) {
        this->time--;
    }
}
