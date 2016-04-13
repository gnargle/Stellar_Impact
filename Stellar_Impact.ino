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
  if (countdown >0) countdown--;
  score = 0;
  arduboy.drawBitmap(0,0,StellarImpactTitle,128,64,WHITE);
  high_score = read_High_Score();
  char port[6] = "";
  sprintf(port, "%i", high_score);
  debug(port,3,28);
  if (death_countdown != 0){ death_countdown--; return;}

  if (arduboy.pressed(DOWN_BUTTON) && countdown == 0){
    audio_enabled = !audio_enabled;
    countdown = 30;
    if (audio_enabled == true){
      audio.on();
      tune.tone(200, 300);
      }
    else{audio.off();}
  }
  if (audio_enabled == false){
    debug("Muted",3,55);
  }
  if (arduboy.pressed(A_BUTTON)||arduboy.pressed(B_BUTTON)) {
    audio.saveOnOff();
    if (audio_enabled)tune.tone(700, 150);
    gameBegun = true; 
    player_HP = 3; 
    player_is_alive = true;
    countdown = 30;
    star_create_gamestart();
  }
}

void setup() {
  // initiate arduboy instance
  arduboy.begin();
  arduboy.initRandomSeed();
  player_x = 0;
  player_y = (HEIGHT / 2);
  audio_enabled = read_EEPROM(EEPROM_AUDIO_ON_OFF);
  if (audio_enabled == true){audio.on();}
  else{audio.off();}
  
}

void loop() {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame())) return;
  arduboy.clear();
  if (!gameBegun) {
    title_menu(); 
    //debug("new",0,0);
    arduboy.display();
  }
  else if(gamePaused){
    //timeGo = false;
    set_led(0,0);
    enemies_update(enemy_arr);
    create_enemies();
    starfield_update(starfield_arr);
    create_stars();
    item_arr_update(item_arr);
    check_pause_combo();
    player_draw_pause();
    draw_ui();
  }
  else{
    if(led_countdown > 0){
      set_led(which_led, led_countdown);
    }
    else{
      set_led(0,0);
    }
    if (led_countdown >0) led_countdown--;
    enemies_update(enemy_arr);
    create_enemies();
    starfield_update(starfield_arr);
    create_stars();
    item_arr_update(item_arr);
    check_pause_combo();
    player_update();
    draw_ui();
  }
  if (gameBegun)arduboy.display();
}



