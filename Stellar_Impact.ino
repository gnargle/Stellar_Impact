#include <EEPROM.h>

#include "Arduboy.h"
#include "globals.h"
#include "image_data.h"
#include "inv.h"
#include "items.h"
#include "enemy.h"
#include "starfield.h"
#include "helper_functions.h"
#include "player.h"


//Arduboy arduboy;

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8



void title_menu(){
    score = 0;
    arduboy.drawBitmap(0,0,StellarImpactTitle,128,64,WHITE);
    high_score = read_High_Score();
    char port[6] = "";
    sprintf(port, "%i", high_score);
    debug(port,2,28);
    if (death_countdown != 0){ death_countdown--; return;}
    if (arduboy.pressed(A_BUTTON)||arduboy.pressed(B_BUTTON)) {
      gameBegun = true; 
      player_HP = 3; 
      player_is_alive = true;
      star_create_gamestart();
      }
}

void setup() {
  // initiate arduboy instance
  arduboy.begin();
  arduboy.initRandomSeed();
  player_x = 0;
  player_y = (HEIGHT / 2);
}

void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame())) return;
  arduboy.clear();
  if (!gameBegun) {
    title_menu(); 
    arduboy.display();
  }
  else{
    enemies_update(enemy_arr);
    create_enemies();
    starfield_update(starfield_arr);
    create_stars();
    item_arr_update(item_arr);
    player_update();
    draw_ui();
    //write_High_Score();
  }
  if (gameBegun)arduboy.display();
}



