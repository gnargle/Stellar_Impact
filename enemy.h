#define SMALL 0
#define MEDIUM 1
#define BIG 2
#define BOSS 3

class Enemy{
  public:
    static const byte startX = WIDTH;
    byte startY = random(8, HEIGHT-8);
    byte framedelay = 3;
    byte shotdelay = 90;
    byte shotxs[6];
    byte shotys[6];
    byte shot_count = 0;
    byte x = startX;
    byte y = startY;
    byte enemy_type = SMALL;
    byte score_worth = 1;
    byte width = 8; // small = 8, med = ?, big = ?, boss = ?
    byte height = 8; // small = 8, med = ?, big = ?, boss = ?
    int HP = 1;
    boolean isEnemy = false;

  void enemy_update(){
    switch (enemy_type){
      case SMALL: update_enemy_small();
      case MEDIUM: update_enemy_med();
      case BIG: update_enemy_big();
      case BOSS: update_enemy_boss(); 
    }
  }

  void death_stuff(){
    isEnemy = false;
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
      if ((shotxs[i]+4 >= player_x && shotxs[i]+4 <= player_x + 16 &&
      shotys[i]+6 >= player_y && shotys[i]+6 <= player_y + 8) || 
      (shotxs[i]+8 >= player_x && shotxs[i]+8 <= player_x + 16 &&
      shotys[i]+8 >= player_y && shotys[i]+8 <= player_y +8)){
        shotxs[i] = WIDTH+10;
        shotys[i] = HEIGHT+10;
        if (player_inv_countdown <=0){
          player_HP--;
          player_invincibility(invincibility_length);
        }
      }
      
      if(timeGo == false){
        arduboy.drawBitmap(shotxs[i],shotys[i],enemyshot,8,8,WHITE);
      }
      else{
        if (shotxs[i] != WIDTH+10 && shotys[i] != HEIGHT+10){
          if (shotxs[i] <= 0 || shotxs[i] >= WIDTH){
            shotxs[i] = WIDTH+10;
            shotys[i] = HEIGHT+10;
          }
          else{
            arduboy.drawBitmap(shotxs[i],shotys[i],enemyshot,8,8,WHITE);
            shotxs[i]--;
            
          }
        }
      }
    }
  }

  void check_enemy_collision_with_player(){
    
    if ((x >= player_x && x <= player_x + 16 &&
      y >= player_y && y <= player_y + 8) || 
      (x+width >= player_x && x+width <= player_x + 16 &&
      y+height >= player_y && y+height <= player_y +8)){
        if (player_inv_countdown <=0){
          HP--;
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
        arduboy.drawBitmap(x,y,smallenemy1,7,8,WHITE);
        last_enem_spr = 1;
      }
    }
    else{
      if (last_enem_spr = 0)arduboy.drawBitmap(x,y,smallenemy,8,8,WHITE);
      else if (last_enem_spr = 1)arduboy.drawBitmap(x,y,smallenemy1,7,8,WHITE);
    }
    check_enemy_collision_with_player();
    check_off_screen();
    check_HP();
    shoot();
    
  }
  void update_enemy_med(){
    
  }

  void update_enemy_big(){
    
  }

  void update_enemy_boss(){
    
  }
    
};

void enemies_update(Enemy* enemy_array){
  for (int i = 0; i <= 14; i++){
    if(enemy_array[i].isEnemy == true){
      enemy_array[i].enemy_update();
    }
  }
}

