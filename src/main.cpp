#include "chip8/components/chip8.hpp"
#include <unistd.h>

int main() {
    Chip8TE emulator;
    
    // Asumsi file ROM logo IBM bernama ibm_logo.ch8 dan diletakkan sejajar dengan eksekusi
    // Sesuaikan path jika file-nya ada di tempat lain.
    emulator.load_program("ibm_logo.ch8");

    // Main loop emulator
    while (true) {
        emulator.emulate_cycle();
        
        // Timer delay hardware CHIP-8 (~60Hz biasanya ditangani terpisah,
        // tapi kita batasi siklus CPU agar tidak berjalan terlalu cepat)
        usleep(2000); // 2 milidetik per siklus (~500Hz)
    }

    return 0;
}
