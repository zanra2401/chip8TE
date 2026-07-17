#pragma once
#include "typedef.hpp"

struct Vector2d_s {
    short x;
    short y;

    Vector2d_s(short x, short y) 
        :x(x), y(y) {}

    Vector2d_s() 
        :x(0), y(0) {}

    bool operator==(const Vector2d_s&) const = default;
};

struct ColorRGB_s {
  short r;
  short g;
  short b;
  bool empty;

  ColorRGB_s(short r, short g, short b): r(r), g(g), b(b), empty(false) {}
  ColorRGB_s(): r(0), g(0), b(0), empty(true) {}
  bool operator==(const ColorRGB_s&) const = default;
};
