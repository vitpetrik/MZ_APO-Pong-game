#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"

//#define _POSIX_C_SOURCE 200112L

typedef struct ball{
  int posx, posy;
  char color;
} ball;

typedef struct player {
  char* nick;
  bool winner;
  char color;
  int score;
  int position;   //player position 0-(sizey-size)
  int size;       //player size 
} player;

typedef struct display_data {
  unsigned char* lcd_membase;
  player player1, player2;
  int sizex, sizey;
} display_data;

#endif