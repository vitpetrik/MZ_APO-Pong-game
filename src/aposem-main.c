#include "config.h"
#include "display.h"
#include "game.h"

int main(int argc, char *argv[]){
  /* Serialize execution of applications */
  /* Try to acquire lock the first */
  if (serialize_lock(1) <= 0) {
    printf("System is occupied\n");

    if (1) {
      printf("Waitting\n");
      /* Wait till application holding lock releases it or exits */
      serialize_lock(0);
    }
  }

  display_data display;
  display.lcd_membase = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  unsigned char *led_membase = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if(display.lcd_membase==NULL || led_membase==NULL)
    exit(EXIT_FAILURE);

  parlcd_hx8357_init(display.lcd_membase);

  init_structure(&display);

  display.player1.nick = (argc>1)?argv[1]:"Player_1";
  display.player2.nick = (argc>2)?argv[1]:"Player_2";

  printf("Application by PONG-GAME by Lendvorsky & Petrik started!\n");

  struct timespec loopdelay;
  loopdelay.tv_sec = 0;
  loopdelay.tv_nsec = 1000000;


  centerPlayers(&display);
  centerBall(&display);

  bool game = true;

  int counter = 0;
  while(game){
    bool update = false;
    if(counter == 10){
      move(&display);
      counter = 0;
      update = true;
    }
    else
      counter++;

    if(update){
      draw_display(&display);
    }
    nanosleep(&loopdelay, NULL);
  }
  serialize_unlock();
  return 0;
}
