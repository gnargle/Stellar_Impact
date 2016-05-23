#define SMALL 0
#define MEDIUM 1
#define BIG 2
#define BOSS 3
#define Y_MIN 8
#define Y_MAX (HEIGHT - 8)
#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8

void debug(char* debug_text, int x, int y){
  //max size 21
  arduboy.setCursor(x,y);
  arduboy.print(debug_text);  
}

void set_led(byte colour, byte value){
  if (colour == 1){
    arduboy.setRGBled(value,0,0);
  }
  else if(colour == 2){
    arduboy.setRGBled(0,value,0);
  }
  else if(colour == 3){
    arduboy.setRGBled(0,0,value);
  }
  else{
    arduboy.setRGBled(0,0,0);
  }
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
  newenemy.y = random(Y_MIN, Y_MAX - 8);
  newenemy.on_spawn();
  enemy_arr[enemy_count + 1] = newenemy;
  big_countdown = 300;
}

void create_enemy_boss(){
  boss_on_screen = true;
  Enemy newenemy;
  newenemy.isEnemy = true;
  newenemy.framedelay = 5;
  newenemy.enemy_type = BOSS;
  newenemy.score_worth = 100;
  newenemy.width = 32;
  newenemy.height = 56;
  newenemy.HP = 20;
  newenemy.shotdelayinitial = 20;
  newenemy.shotdelay = 20;
  newenemy.y = random(Y_MIN, Y_MAX-10);
  newenemy.on_spawn();
  enemy_arr[enemy_count + 1] = newenemy;
  boss_countdown = 3600;
}

void create_enemies(){
  if (!timeGo || gamePaused || boss_on_screen)return;
  if (enemy_countdown == 0){
      if (enemy_count < max_enemies){
        if (enemy_arr[enemy_count+1].isEnemy == false){
          byte ran = random(0,4);
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
          if (ran == BOSS){
            if (boss_countdown == 0){
              create_enemy_boss();
            }
            else{
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
        }
        enemy_count +=1;
      }
      if (enemy_count >= max_enemies || enemy_count < 0 || enemy_count ==256) enemy_count = 0;
      enemy_countdown = enemy_countdown_initial;
  }
  else {enemy_countdown--;}
  if (med_countdown > 0) med_countdown--;
  if (big_countdown >0) big_countdown--;
  if (boss_countdown >0) boss_countdown--;
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
  if(!timeGo || gamePaused) return;
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
  if (gamePaused){
    arduboy.setCursor((WIDTH/2) - ((sizeof("Paused") - 1) * CHAR_WIDTH /2)
    , (HEIGHT/2) - (CHAR_HEIGHT / 2));
    arduboy.print("Paused");
    if(audio_countdown == 0 && arduboy.pressed(DOWN_BUTTON) && !(arduboy.pressed(UP_BUTTON))
    && !(arduboy.pressed(LEFT_BUTTON)) && !(arduboy.pressed(RIGHT_BUTTON))){
      audio_enabled = !audio_enabled;
      audio_countdown = 30;
      if (audio_enabled == true){
        audio.on();
        tune.tone(200, 300);
        }
      else{audio.off();}
    }
    if (audio_enabled == false){
      arduboy.setCursor(3,55);
      arduboy.print("Muted");
    }
    if(audio_countdown > 0) audio_countdown--;
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
  boss_countdown = 3600;
  countdown = 30;
  player_x = 0;
  player_y = (HEIGHT / 2);
  player_last_HP = player_HP;
  player_inv_countdown = 0;
  bomb_num = 3;
  bomb_countdown = 0;
  bomb_rad = 0;
  for (int i=0; i <= max_enemies; i++){
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

void check_secret(){ //0 = u, 1 = d, 2= l, 3= r
  
  
  if (secret[0]==2 && secret[1]== 3 && secret[2] == 2 && secret[3] == 3 && 
  secret[4] == 1 && secret [5] == 1 && secret[6] == 0 && secret[7] == 0){
    arduboy.clear();
    arduboy.setCursor((WIDTH/2) - ((sizeof("For Robyn.") - 1) * CHAR_WIDTH /2)
    , (HEIGHT/2) - (CHAR_HEIGHT / 2));
    arduboy.print("For Robyn.");
    arduboy.drawBitmap(WIDTH/2 - 4,10+(HEIGHT/2) - (CHAR_HEIGHT / 2), heart, 8,8,WHITE);
  }
  else{
    if (countdown == 0){
      if (arduboy.pressed(UP_BUTTON)){
        secret[secret_tracker] = 0;
        secret_tracker++;
        countdown = 10;
      }
      if (arduboy.pressed(DOWN_BUTTON)){
        secret[secret_tracker] = 1;
        secret_tracker++;
        countdown = 10;
      }
      if (arduboy.pressed(LEFT_BUTTON)){
        secret[secret_tracker] = 2;
        secret_tracker++;
        countdown = 10;
      }
      if (arduboy.pressed(RIGHT_BUTTON)){
        secret[secret_tracker] = 3;
        secret_tracker++;
        countdown = 10;
      }
      if(secret[0] !=2 && secret[0] != 5){
        for (int i = 0; i<8; i++){
          secret[i] = 5;
        }
        secret_tracker = 0;
      }
      if(secret[1] != 3 && secret[1] != 5){
        for (int i = 0; i<8; i++){
          secret[i] = 5;
        }
        secret_tracker = 0;
      }
      if(secret[2] != 2 && secret[2] != 5){
        for (int i = 0; i<8; i++){
          secret[i] = 5;
        }
        secret_tracker = 0;
      }
      if(secret[3] != 3 && secret[3] != 5){
        for (int i = 0; i<8; i++){
          secret[i] = 5;
        }
        secret_tracker = 0;
      }
      if(secret[4] != 1 && secret[4] != 5){
        for (int i = 0; i<8; i++){
          secret[i] = 5;
        }
        secret_tracker = 0;
      }
      if(secret[5] != 1 && secret[5] != 5){
        for (int i = 0; i<8; i++){
          secret[i] = 5;
        }
        secret_tracker = 0;
      }
      if(secret[6] != 0 && secret[6] != 5){
        for (int i = 0; i<8; i++){
          secret[i] = 5;
        }
        secret_tracker = 0;
      }
      if(secret[7] != 0 && secret[7] != 5){
        for (int i = 0; i<8; i++){
          secret[i] = 5;
        }
        secret_tracker = 0;
      }
    }
    else if (countdown >0) {countdown--;}
  }
}

