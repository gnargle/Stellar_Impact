

void debug(char* debug_text, int x, int y){
  //max size 21
  arduboy.setCursor(x,y);
  arduboy.print(debug_text);  
}

void create_enemies(){
  if (!timeGo)return;
  if (enemy_countdown == 0){
      if (enemy_count < 14){
        if (enemy_arr[enemy_count+1].isEnemy == false){
          Enemy newenemy;
          newenemy.isEnemy = true;
          newenemy.on_spawn();
          enemy_arr[enemy_count + 1] = newenemy;
        }
        enemy_count +=1;
      }
      if (enemy_count >= 14 || enemy_count < 0 || enemy_count ==256) enemy_count = 0;
      enemy_countdown = enemy_countdown_initial;
  }
  else {enemy_countdown--;}
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
  byte val_arr[2];
  short hs;
  for (int i = 0; i<=1; i++){
    val = read_EEPROM(addr+i);
    if (val == 255) {
      // if the EEPROM value is 255, it's uninitialised.
      // so we initialise it with a score of 100.
      if (i == 1){
        write_EEPROM(addr+i, 100); 
        val = 1;
      }
      else{
        write_EEPROM(addr+i,0);
        val = 0;
      }
    }
    val_arr[i] = val;
  }
  //by this point, we have a 2 value array containing the high and low bytes of high score.
  //so we or them together with the high byte bitshifted to create a high score short
  hs = (val_arr[0] << 8) | val_arr[1];
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

