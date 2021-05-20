#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <stdint.h>

// TODO text ouput

void canvas_init(uint16_t *frame_buffer, uint16_t w, uint16_t h);

void canvas_drawPixel(int16_t x, int16_t y, uint16_t color);

void canvas_drawHline(int16_t x, int16_t y, int16_t size, uint16_t color);

void canvas_drawVline(int16_t x, int16_t y, int16_t size, uint16_t color);

void canvas_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void canvas_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void canvas_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void canvas_fillScreen(uint16_t color);

#endif