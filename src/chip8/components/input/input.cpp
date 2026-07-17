#include "input.hpp"
#include <iostream>

void Input::process() {
    // Implementasi pembacaan keyboard dari sistem window atau terminal (tergantung implementasi platform)
    // Untuk saat ini dibiarkan kosong sebagai stub
}

bool Input::is_key_pressed(uint8_t key) {
    if (key > 0xF) return false;
    return key_state[key];
}
