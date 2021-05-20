#include "display.h"
#include "canvas/canvas.h"

// TODO text ouput

void draw_display(display_data *data) {
  uint16_t *frame_buffer = calloc(LCD_WIDTH * LCD_HEIGHT, sizeof(uint16_t));
  canvas_init(frame_buffer, LCD_WIDTH, LCD_HEIGHT);

  int playgroud_offset_x = (LCD_WIDTH-data->playgroud.xsize)/2;
  int playgroud_offset_y = (LCD_WIDTH-data->playgroud.ysize)/2;

  canvas_drawRect(playgroud_offset_x, playgroud_offset_y, data->playgroud.xsize, data->playgroud.ysize, 0xff);

  canvas_fillRect(playgroud_offset_x + data->ball.posx, playgroud_offset_y + data->ball.posy, BALL_SIZE, BALL_SIZE, data->ball.color);
  canvas_fillRect(playgroud_offset_x + data->player1.offset, playgroud_offset_y + data->player1.position - data->player1.size/2, -RACKET_WIDTH, data->player1.size, data->player1.color);
  canvas_fillRect(playgroud_offset_x + data->player2.offset, playgroud_offset_y + data->player2.position - data->player2.size/2, RACKET_WIDTH, data->player2.size, data->player1.color);

  canvas_drawVline(playgroud_offset_x + data->playgroud.xsize/2, playgroud_offset_y, data->playgroud.ysize, 0xFF);

  write_display(data->lcd_membase, frame_buffer);
  free(frame_buffer);
}

void write_display(unsigned char *lcd_membase, uint16_t *frame_buffer) {
  parlcd_write_cmd(lcd_membase, 0x2C);

  for (int i = 0; i < LCD_WIDTH * LCD_HEIGHT; ++i) {
    parlcd_write_data(lcd_membase, frame_buffer[i]);
  }
}

void fill_solid() {}