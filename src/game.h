#ifndef __GAME_H__
#define __GAME_H__

#include "config.h"

void init_structure(display_data *display);
void centerBall(display_data* display);
void centerPlayers(display_data* display);
void move(display_data *display);

#endif