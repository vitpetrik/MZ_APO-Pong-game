#include "canvas.h"
#include <stdio.h>
#include <stdlib.h>

#define SIGN(x) ((x > 0) - (x < 0))

uint16_t _width, _height;
uint16_t *_frame_buffer;

void canvas_init(uint16_t *fb, uint16_t w, uint16_t h) {
  _frame_buffer = fb;
  _width = w;
  _height = h;
}

void canvas_drawPixel(int16_t x, int16_t y, uint16_t color) {
  _frame_buffer[x + _width * y] = color;
}

void canvas_drawHline(int16_t x, int16_t y, int16_t size, uint16_t color) {
  for (int i = 0; i < abs(size); ++i) {
    canvas_drawPixel(x, y, color);
    x += SIGN(size);
  }
}

void canvas_drawVline(int16_t x, int16_t y, int16_t size, uint16_t color) {
  for (int i = 0; i < abs(size); ++i) {
    canvas_drawPixel(x, y, color);
    y += SIGN(size);
  }
}

void canvas_drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                     uint16_t color) {
  canvas_drawHline(x, y, w, color);
  canvas_drawVline(x, y, h, color);
  canvas_drawHline(x, y + h, w, color);
  canvas_drawVline(x + w, y, h, color);
}

void canvas_fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                     uint16_t color) {
  for (int i = 0; i < abs(h); ++i) {
      canvas_drawHline(x, y, w, color);
      y += SIGN(h);
  }
}

void canvas_fillScreen(uint16_t color) {
    canvas_fillRect(0, 0, _width, _height, color);
}