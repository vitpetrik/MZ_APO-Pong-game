#include "display.h"
#include "game.h"

bool move(display_data *display){
  display->ball.posx += display->ball.stepx;
  display->ball.posy += display->ball.stepy;

  if(display->ball.posy>=display->playgroud.ysize || display->ball.posy <= 0){
    display->ball.stepy *= -1;
  }

  if(display->ball.posx>=display->playgroud.xsize){
    if(score(display, &display->player1))
      return true;
  }

  if(display->ball.posx <= 0){
    if(score(display, &display->player2))
      return true;
  }

  if(display->ball.posx == display->player1.offset && display->ball.posy>=(display->player1.position-display->player1.size/2) && display->ball.posy<=(display->player1.position+display->player1.size/2)){
    display->ball.stepx *= -1;
    beep(true, display->led_membase);
  }

  if(display->ball.posx == display->player2.offset && display->ball.posy>=(display->player2.position-display->player2.size/2) && display->ball.posy<=(display->player2.position+display->player2.size/2)){
    display->ball.stepx *= -1;
  }
  printf("ball position %d %d\n", display->ball.posx, display->ball.posy);
  return false;
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

  display->player1.size = 50;
  display->player1.offset = 10;
  display->player1.score = 0;
  display->player2.size = 50;
  display->player2.offset = 390;
  display->player2.score = 0;
  updateScoreLeds(display);
}

void beep(bool state, void* ledbase){
  if(state){
    *(volatile uint32_t*)(ledbase+AUDIOPWM_REG_PWMPER_o) = 1000000;
    *(volatile uint32_t*)(ledbase+AUDIOPWM_REG_PWMPER_o) = 500000;
  }
}

bool score(display_data *display, player *scorer){
  printf("Goal scored by %s\n", scorer->nick);
  scorer->score++;
  updateScoreLeds(display);

  if(scorer->score>16){
    scorer->winner = true;
    return true;
  }
  //here celebrate      
  centerBall(display);
  centerPlayers(display);
  return false; 
}

void updateScoreLeds(display_data* display){
  uint16_t line_score_p1 = 0;
  uint16_t line_score_p2 = 0;
  for(int i=0; i<display->player1.score; i++){
    line_score_p1 |= 1<<(16-i);
  }
  for(int i=0; i<display->player2.score; i++){
    line_score_p1 |= 1<<(i);
  }
  *(volatile uint32_t*)(display->led_membase+SPILED_REG_LED_LINE_o) = line_score_p1<<16 | line_score_p2;
}

knobs readKnobs(display_data* display){
  uint32_t value = *(volatile uint32_t*)(display->led_membase + SPILED_REG_KNOBS_8BIT_o);
  knobs ret = {
    .bknob = value&0x0000000FF,
    .gknob = (value&0x00000FF00)>>8,
    .rknob = (value&0x000FF0000)>>16
  };
  printf("%d %d %d\n", ret.rknob, ret.gknob, ret.bknob);
  return ret;
}