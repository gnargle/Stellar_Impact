#include "Arduboy.h"
#include "globals.h"
#include "image_data.h"
#include "inv.h"
#include "enemy.h"
#include "starfield.h"
#include "class_arrays.h"
#include "helper_functions.h"
#include "player.h"

//Arduboy arduboy;

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8



void title_menu(){
    score = 0;
    arduboy.drawBitmap(0,0,StellarImpactTitle,128,64,WHITE);
    /*arduboy.setCursor((WIDTH/2) - ((sizeof("Press fire") - 1) * CHAR_WIDTH /2)
    , (HEIGHT/2) - (CHAR_HEIGHT / 2));
    arduboy.print("Press fire");
    arduboy.setCursor((WIDTH/2) - ((sizeof("to start") - 1) * CHAR_WIDTH /2)
    , (HEIGHT/2) - (CHAR_HEIGHT / 2) + 10);
    arduboy.print("to start");*/
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
    player_update();
    if (score > 100 || score < 0){
      debug("glitch m8", 0, 47);
    }
    //char port[10] = "";
    //short *ip = NULL; 
    //ip = &score-1;
    //sprintf(port, "%i", (void*) *ip); // ok, so 0x366 is the score's location in mem
    //debug(port, 0, 54);
    draw_ui();
  }
  if (gameBegun)arduboy.display();
}



