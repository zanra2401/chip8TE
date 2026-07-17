#pragma once
#include "screen.hpp"
#include <vector>

struct Pixel_s {
  Vector2d_s pos;
  ColorRGB_s color;
  Pixel_s() : pos(Vector2d_s()), color(ColorRGB_s(255,255,255)) {};
  Pixel_s(Vector2d_s pos) : pos(pos), color(ColorRGB_s(255,255,255)) {};
  Pixel_s(Vector2d_s pos, ColorRGB_s color) : pos(pos), color(color) {};
};

typedef std::vector<Pixel_s> Object_t;
