#ifndef __GAME_H__
#define __GAME_H__

#include "config.h"

void init_structure(display_data *display);
void centerBall(display_data* display);
void centerPlayers(display_data* display);
bool move(display_data *display);
bool score(display_data *display, player *scorer);
void updateScoreLeds(display_data* display);
knobs readKnobs(display_data* display);
void beep(bool state, void* ledbase);

#endif