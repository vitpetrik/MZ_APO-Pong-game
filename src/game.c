#include "display.h"

void move(display_data *display){
    display->ball.posx += display->ball.stepx;
    display->ball.posy += display->ball.stepy;

    if(display->ball.posy>=display->playgroud.ysize || display->ball.posy <= 0){
      display->ball.stepy *= -1;
    }

    if(display->ball.posx>=display->playgroud.xsize){
      printf("goal scored by player 1\n");
      centerBall(&display);
      centerPlayers(&display);
    }

    if(display->ball.posx <= 0){
      printf("goal scored by player 2\n");
      centerBall(&display);
      centerPlayers(&display);
    }

    if(display->ball.posx == display->player1.offset && display->ball.posy>(display->player1.position-display->player1.size/2) && display->ball.posy<(display->player1.position+display->player1.size/2)){
      display->ball.stepx *= -1;
    }

    if(display->ball.posx == display->player2.offset && display->ball.posy>(display->player2.position-display->player2.size/2) && display->ball.posy<(display->player2.position+display->player2.size/2)){
      display->ball.stepx *= -1;
    }
    printf("ball position %d %d\n", display->ball.posx, display->ball.posy);
}

void centerBall(display_data* display){
  display->ball.posx = display->playgroud.xsize/2;
  display->ball.posy = display->playgroud.ysize/2;
}

void centerPlayers(display_data* display){
  display->player1.position = display->playgroud.ysize/2;
  display->player2.position = display->playgroud.ysize/2;
}

void init_structure(display_data *display){
  display->playgroud.xsize = 400;
  display->playgroud.ysize = 300;
  display->ball.stepx = 1;
  display->ball.stepy = 1;

  display->player1.size = 300;
  display->player1.offset = 10;
  display->player2.size = 300;
  display->player2.offset = 390;
}