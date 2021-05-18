#include "config.h"
#include "display.h"

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

  display.player1.nick = (argc>1)?argv[1]:"Player_1";
  display.player2.nick = (argc>2)?argv[1]:"Player_2";

  printf("Application by PONG-GAME by Lendvorsky & Petrik started!\n");

  bool game = true;
  /*
  while(game){
    
  }
  */
  parlcd_hx8357_init(display.lcd_membase);
  
  draw_display(&display);

  serialize_unlock();
  return 0;
}
