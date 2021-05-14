#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "serialize_lock.h"

//#define _POSIX_C_SOURCE 200112L

typedef struct player {
  char nick[10];
  bool winner;
  char color;
  int score;
} player;

typedef struct display_data {
  unsigned char* lcd_membase;
  player player1, player2;
} display_data;

#endif