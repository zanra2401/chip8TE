#include "rendering_engine/tEngine.hpp"
#include "chip8/program_loader/program_loader.hpp"

int main() {

    PLoader loader = PLoader();
    loader.load_from_file("./Soccer.ch8");
    loader.ddebug();
    return 0;
}
