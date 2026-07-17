#include "./graphic.hpp" 


Graphic::Graphic() {
  engine = TEngine({64, 32});
}

void Graphic::disp_clear() {
  engine.clear_screen();
}
