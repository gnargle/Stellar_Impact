#define SMALL 0
#define MEDIUM 1
#define BIG 2
#define BOSS 3
#define Y_MIN 8
#define Y_MAX (HEIGHT - 8)

void debug(char* debug_text, int x, int y){
  //max size 21
  arduboy.setCursor(x,y);
  arduboy.print(debug_text);  
}


void create_enemy_small(){ // small is the default so we don't have to change much
  Enemy newenemy;
  newenemy.isEnemy = true;
  newenemy.on_spawn();
  enemy_arr[enemy_count + 1] = newenemy;
}

void create_enemy_med(){
  Enemy newenemy;
  newenemy.isEnemy = true;
  newenemy.framedelay = 2;
  newenemy.enemy_type = MEDIUM;
  newenemy.score_worth = 5;
  newenemy.shotdelayinitial = 50;
  newenemy.shotdelay = 50;
  newenemy.on_spawn();
  enemy_arr[enemy_count + 1] = newenemy;
}

void create_enemy_big(){
  Enemy newenemy;
  newenemy.isEnemy = true;
  newenemy.framedelay = 5;
  newenemy.enemy_type = BIG;
  newenemy.score_worth = 10;
  newenemy.width = 16;
  newenemy.height = 16;
  newenemy.HP = 4;
  newenemy.shotdelayinitial = 70;
  newenemy.shotdelay = 70;
  newenemy.y = random (Y_MIN, Y_MAX - 8);
  newenemy.on_spawn();
  enemy_arr[enemy_count + 1] = newenemy;
  big_countdown = 300;
}

void create_enemies(){
  if (!timeGo)return;
  if (enemy_countdown == 0){
      if (enemy_count < 9){
        if (enemy_arr[enemy_count+1].isEnemy == false){
          byte ran = random(0,3);
          if (ran == SMALL){ 
            create_enemy_small();
          }
          if (ran == MEDIUM){
            if (med_countdown == 0){
              create_enemy_med();
            }
            else{
              create_enemy_small();
            }
          }
          if (ran == BIG){
            if (big_countdown == 0){
              create_enemy_big();
            }
            else{
              if (med_countdown == 0){
                create_enemy_med();
              }
              else{
                create_enemy_small();
              }
            }
          }
        }
        enemy_count +=1;
      }
      if (enemy_count >= 9 || enemy_count < 0 || enemy_count ==256) enemy_count = 0;
      enemy_countdown = enemy_countdown_initial;
  }
  else {enemy_countdown--;}
  if (med_countdown > 0) med_countdown--;
  if (big_countdown >0) big_countdown--;
}

void star_create_depth(byte depth){
  if (star_count <=29){
    if (starfield_arr[star_count+1].star_exists == false){
      Star newstar;
      newstar.star_exists = true;
      newstar.depth = depth;
      starfield_arr[star_count+1] = newstar;
    }
    star_count += 1;
  }
    if (star_count > 29) star_count = 0;
}

void create_stars(){
  if(!timeGo) return;
  if (star_countdown_depth == 0){
    star_create_depth(random(1,4));
    star_countdown_depth = star_countdown_initial_depth;
  }
  star_countdown_depth--;
}

void star_create_gamestart(){
  for (int i = 0; i <= 30; i++){
    Star newstar;
    newstar.star_exists = true;
    newstar.depth = random(1,4);
    newstar.x = random(1,WIDTH);
    starfield_arr[i] = newstar;
  }
}

void draw_ui(){
  arduboy.drawBitmap(0,0,heart,8,8,WHITE);
  arduboy.setCursor(10,0);
  char port[3] = "";
  sprintf(port, "x%i", player_HP);
  arduboy.print(port);
  arduboy.drawBitmap(24+4,0,bomb,8,8,WHITE);
  arduboy.setCursor(36+4,0);
  sprintf(port, "x%i", bomb_num);
  arduboy.print(port);
  arduboy.setCursor(50+8,0);
  arduboy.print("Score:");
  char port1[3] = "";
  sprintf(port1, "%i", score);
  arduboy.setCursor(86+8,0);
  arduboy.print(port1);
}

byte read_EEPROM(int address){
  byte val;
  val = EEPROM.read(address);
  return val;
}

void write_EEPROM(int address, int val){
  EEPROM.update(address, val);
}

short read_High_Score(){
  // score should be 2 bytes long since we're using a short
  // we will use bytes 54 and 55
  //byte 54 is high byte, byte 55 is low byte
  byte addr = 54;
  byte val;
  byte val1;
  byte val_arr[2];
  short hs;
    val = read_EEPROM(addr);
    val1 = read_EEPROM(addr+1);
    if (val == 255 && val1 == 255) {
      // if the EEPROM value is 255, it's uninitialised.
      // so we initialise it with a score of 100.
        write_EEPROM(addr+1, 100); 
        val = 100;
        write_EEPROM(addr,0);
        val1 = 0;
    }
    val_arr[0] = val;
  //by this point, we have a 2 value array containing the high and low bytes of high score.
  //so we or them together with the high byte bitshifted to create a high score short
  hs = (val << 8) | val1;
  return hs;
}

void write_High_Score(){
  if (score > high_score){
    byte val;
    byte val1;
    val = score & 0xFF; // get low byte of score
    write_EEPROM(55,val);
    val1 = (score >> 8) & 0xFF; // get high byte of score
    write_EEPROM(54,val1);
  }
}

void reset_default_values(){
  score_recorded = false;
  score = 0;
  gameBegun = 0;
  enemy_count = 0;
  enemy_countdown = enemy_countdown_initial;
  med_countdown = 900;
  big_countdown = 2400;
  countdown = 30;
  player_x = 0;
  player_y = (HEIGHT / 2);
  player_last_HP = player_HP;
  player_inv_countdown = 0;
  bomb_num = 3;
  bomb_countdown = 0;
  bomb_rad = 0;
  for (int i=0; i <= 9; i++){
    enemy_arr[i].death_stuff();
  }
  for (int i=0; i<=16; i++){
    bx[i] = NULL;
    by[i] = NULL;
  }
  for (int i=0; i<=5;i++){
    item_arr[i].isItem = false;
  }
}

