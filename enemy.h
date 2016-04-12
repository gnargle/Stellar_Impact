#define SMALL 0
#define MEDIUM 1
#define BIG 2
#define BOSS 3
#define UP true
#define DOWN false
#define Y_MIN 8
#define Y_MAX (HEIGHT - 8)

class Enemy{
  public:
    static const byte startX = WIDTH;
    byte startY = random(Y_MIN, Y_MAX);
    byte framedelay = 3;
    byte shotdelayinitial=90;
    byte shotdelay = shotdelayinitial;
    byte shotxs[6];
    byte shotys[6];
    byte shot_count = 0;
    byte x = startX;
    byte y = startY;
    byte enemy_type = SMALL;
    byte score_worth = 1;
    byte width = 8; // small = 8, med = 8, big = 16, boss = ?
    byte height = 8; // small = 8, med = 8, big = 16, boss = ?
    int HP = 1;
    boolean v_dir = random(0,2);
    boolean isEnemy = false;

  void enemy_update(){
    switch (enemy_type){
      case SMALL: update_enemy_small(); return;
      case MEDIUM: update_enemy_med(); return;
      case BIG: update_enemy_big(); return;
      case BOSS: update_enemy_boss(); return;
    }
  }

  void death_stuff(){
    isEnemy = false;
    if (random(0,44) == 0){
      Item newitem;
      newitem.x = x;
      newitem.y = y;
      newitem.movement_rate = framedelay;
      if(random(0,2) == 0){
        newitem.itemType = false;
      }
      else{
        newitem.itemType = true;
      }
      newitem.isItem = true;
      for(int i = 0; i<=5;i++){
        if (item_arr[i].isItem == false){
          item_arr[i] = newitem;
          break;
        }
      }
    }
    x = NULL;
    y = NULL;
    for (int i = 0; i<6; i++){
      shotxs[i] = WIDTH+10;
      shotys[i] = HEIGHT+10;
    }
    shot_count = 0;
  }

  void on_spawn(){
    for (int i = 0; i<6; i++){
      shotxs[i] = WIDTH+10;
      shotys[i] = HEIGHT+10;
    }
    shot_count = 0;
  }

  void check_HP(){
    if (HP <= 0){
      death_stuff();
      score+= score_worth; 
    }
  }

  void check_off_screen(){
    if (x == 0) {
      death_stuff();
    }
  }

  void shoot(){
    if (timeGo){
      if (shotdelay == 0){
        shotxs[shot_count] = x - 6;
        shotys[shot_count] = y;
        shot_count++;
        if (shot_count > 6) shot_count = 0;
        shotdelay = 90;
      }
      else{
        shotdelay--;
      }
    }
    for (int i = 0; i<=5; i++){
      if (enemy_type == SMALL){
        if ((shotxs[i]+4 >= player_x && shotxs[i]+4 <= player_x + 16 &&
        shotys[i]+7 >= player_y && shotys[i]+7 <= player_y + 8) || 
        (shotxs[i]+8 >= player_x && shotxs[i]+8 <= player_x + 16 &&
        shotys[i]+8 >= player_y && shotys[i]+8 <= player_y +8)){
          shotxs[i] = WIDTH+10;
          shotys[i] = HEIGHT+10;
          if (player_inv_countdown <=0){
            player_HP--;
            player_invincibility(invincibility_length);
          }
        }
      }
      else if (enemy_type == MEDIUM){
        if ((shotxs[i] >= player_x && shotxs[i] <= player_x + 16 &&
        shotys[i]+1 >= player_y && shotys[i]+1 <= player_y + 8) || 
        (shotxs[i]+8 >= player_x && shotxs[i]+8 <= player_x + 16 &&
        shotys[i]+1 >= player_y && shotys[i]+1 <= player_y +8) ||
        (shotxs[i] >= player_x && shotxs[i] <= player_x+16 &&
        shotys[i]+7 >= player_y && shotys[i]+7 <= player_y + 8) ||
        (shotxs[i]+8 >= player_x && shotxs[i]+8 <= player_x + 16 &&
        shotys[i]+7 >= player_y && shotys[i]+7 <= player_y +8)){
          shotxs[i] = WIDTH+10;
          shotys[i] = HEIGHT+10;
          if (player_inv_countdown <=0){
            player_HP--;
            player_invincibility(invincibility_length);
          }
        }
      }
      else if (enemy_type == BIG){
        if ((shotxs[i]+10 >= player_x && shotxs[i]+10 <= player_x + 16 &&
        shotys[i]+1 >= player_y && shotys[i]+1 <= player_y + 8) || 
        (shotxs[i]+16 >= player_x && shotxs[i]+16 <= player_x + 16 &&
        shotys[i]+1 >= player_y && shotys[i]+1 <= player_y +8) ||
        (shotxs[i]+10 >= player_x && shotxs[i]+10 <= player_x+16 &&
        shotys[i]+2 >= player_y && shotys[i]+2 <= player_y + 8) ||
        (shotxs[i]+16 >= player_x && shotxs[i]+16 <= player_x + 16 &&
        shotys[i]+2 >= player_y && shotys[i]+2 <= player_y +8) ||
        (shotxs[i]+10 >= player_x && shotxs[i]+10 <= player_x + 16 &&
        shotys[i]+8 >= player_y && shotys[i]+8 <= player_y + 8) || 
        (shotxs[i]+16 >= player_x && shotxs[i]+16 <= player_x + 16 &&
        shotys[i]+8 >= player_y && shotys[i]+8 <= player_y +8) ||
        (shotxs[i]+10 >= player_x && shotxs[i]+10 <= player_x+16 &&
        shotys[i]+9 >= player_y && shotys[i]+9 <= player_y + 8) ||
        (shotxs[i]+16 >= player_x && shotxs[i]+16 <= player_x + 16 &&
        shotys[i]+9 >= player_y && shotys[i]+9 <= player_y +8) ||
        (shotxs[i]+10 >= player_x && shotxs[i]+10 <= player_x + 16 &&
        shotys[i]+14 >= player_y && shotys[i]+14 <= player_y + 8) || 
        (shotxs[i]+16 >= player_x && shotxs[i]+16 <= player_x + 16 &&
        shotys[i]+14 >= player_y && shotys[i]+14 <= player_y +8) ||
        (shotxs[i]+10 >= player_x && shotxs[i]+10 <= player_x+16 &&
        shotys[i]+15 >= player_y && shotys[i]+15 <= player_y + 8) ||
        (shotxs[i]+16 >= player_x && shotxs[i]+16 <= player_x + 16 &&
        shotys[i]+15 >= player_y && shotys[i]+15 <= player_y +8)){
          shotxs[i] = WIDTH+10;
          shotys[i] = HEIGHT+10;
          if (player_inv_countdown <=0){
            player_HP--;
            player_invincibility(invincibility_length);
          }
        }
      }
      
      if(timeGo == false){
        if (enemy_type == SMALL){
          arduboy.drawBitmap(shotxs[i],shotys[i],enemyshot,8,8,WHITE);
        }
        else if (enemy_type == MEDIUM){
          arduboy.drawBitmap(shotxs[i],shotys[i],enemymedshot,8,8,WHITE);
        }
        else if (enemy_type == BIG){
          arduboy.drawBitmap(shotxs[i],shotys[i],enemybigshot,16,16,WHITE);
        }
      }
      else{
        if (shotxs[i] != WIDTH+10 && shotys[i] != HEIGHT+10){
          if (shotxs[i] <= 0 || shotxs[i] >= WIDTH){
            shotxs[i] = WIDTH+10;
            shotys[i] = HEIGHT+10;
          }
          else{
            if (enemy_type == SMALL){
              arduboy.drawBitmap(shotxs[i],shotys[i],enemyshot,8,8,WHITE);
              shotxs[i]--;
            }
            else if (enemy_type == MEDIUM){
              arduboy.drawBitmap(shotxs[i],shotys[i],enemymedshot,8,8,WHITE);
              shotxs[i]--;
            }
            else if (enemy_type == BIG){
              arduboy.drawBitmap(shotxs[i],shotys[i],enemybigshot,16,16,WHITE);
              shotxs[i]--;
            }
          }
        }
      }
    }
  }

  void check_enemy_collision_with_player(){
    if (!player_is_alive) return;
    if((player_x >= x && player_x <= x+width
    && player_y >= y && player_y <= y+height)
    ||(player_x >= x && player_x <= x+width
    && player_y+8 >= y && player_y+8 <= y+height)
    ||(player_x +16 >= x && player_x +16 <= x+width
    && player_y >= y && player_y <= y+height)
    ||(player_x +16 >= x && player_x +16 <= x+width
    && player_y+8 >= y && player_y+8 <= y+height)){
    
  /*if ((x >= player_x && x <= player_x + 16 &&
    y >= player_y && y <= player_y + 8) || 
    (x+width >= player_x && x+width <= player_x + 16 &&
    y+height >= player_y && y+height <= player_y +8)){*/
      HP--;
      if (player_inv_countdown <=0){
        player_HP--;
        player_invincibility(invincibility_length);
      }
    }
  }

  void update_enemy_small(){
    if (arduboy.everyXFrames(framedelay) && timeGo){
      x--;
    }

    if (timeGo){
      if (framecount<15 || (framecount>=30 && framecount<45)){
        arduboy.drawBitmap(x,y,smallenemy,8,8,WHITE);
        last_enem_spr = 0;
      }
  
      else if ((framecount>=15 && framecount<30) || framecount>=45)  {
        arduboy.drawBitmap(x,y,smallenemy1,8,8,WHITE);
        last_enem_spr = 1;
      }
    }
    else{
      if (last_enem_spr = 0)arduboy.drawBitmap(x,y,smallenemy,8,8,WHITE);
      else if (last_enem_spr = 1)arduboy.drawBitmap(x,y,smallenemy1,8,8,WHITE);
    }
    check_enemy_collision_with_player();
    check_off_screen();
    check_HP();
    shoot();
    
  }
  
  void update_enemy_med(){
   if (arduboy.everyXFrames(framedelay) && timeGo){
      x--;
      if (v_dir == UP && y > Y_MIN){
        y--;
      }
      if (y <= Y_MIN){
        v_dir = DOWN;
      }
      if (v_dir == DOWN && y <+ Y_MAX){
        y++;
      }
      if (y >= Y_MAX){
        v_dir = UP;
      }
      
      
    }

    if (timeGo){
      if (framecount<15 || (framecount>=30 && framecount<45)){
        arduboy.drawBitmap(x,y,enemymed,8,8,WHITE);
        last_enem_spr = 0;
      }
  
      else if ((framecount>=15 && framecount<30) || framecount>=45)  {
        arduboy.drawBitmap(x,y,enemymed1,8,8,WHITE);
        last_enem_spr = 1;
      }
    }
    else{
      if (last_enem_spr = 0)arduboy.drawBitmap(x,y,enemymed,8,8,WHITE);
      else if (last_enem_spr = 1)arduboy.drawBitmap(x,y,enemymed1,8,8,WHITE);
    }
    check_enemy_collision_with_player();
    check_off_screen();
    check_HP();
    shoot();
  }

   void update_enemy_big(){
    if (arduboy.everyXFrames(framedelay) && timeGo){
      x--;
    }

    if (timeGo){
      if (framecount<15 || (framecount>=30 && framecount<45)){
        arduboy.drawBitmap(x,y,enemybig,16,16,WHITE);
        last_enem_spr = 0;
      }
  
      else if ((framecount>=15 && framecount<30) || framecount>=45)  {
        arduboy.drawBitmap(x,y,enemybig1,16,16,WHITE);
        last_enem_spr = 1;
      }
    }
    else{
      if (last_enem_spr = 0)arduboy.drawBitmap(x,y,enemybig,16,16,WHITE);
      else if (last_enem_spr = 1)arduboy.drawBitmap(x,y,enemybig1,16,16,WHITE);
    }
    check_enemy_collision_with_player();
    check_off_screen();
    check_HP();
    shoot();
    
  }

  void update_enemy_boss(){
    
  }
    
};

void enemies_update(Enemy* enemy_array){
  for (int i = 0; i <= 9; i++){
    if(enemy_array[i].isEnemy == true){
      enemy_array[i].enemy_update();
    }
  }
}

Enemy enemy_arr[10];
