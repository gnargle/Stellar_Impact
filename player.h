#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8
#define NUM_CHARS (sizeof("a") - 1)
#define X_MIN 8
#define X_MAX (WIDTH - 16)
#define Y_MAX (HEIGHT - 8)

void check_player_buttons(){
  if (arduboy.pressed(RIGHT_BUTTON) && (player_x < X_MAX)) player_x++;
  if (arduboy.pressed(LEFT_BUTTON) && (player_x > 0)) player_x--;
  if (arduboy.pressed(DOWN_BUTTON) && (player_y < Y_MAX)) player_y++;
  if (arduboy.pressed(UP_BUTTON) && (player_y > X_MIN)) player_y--;
  if (arduboy.pressed(B_BUTTON)){
    if (countdown <= 0){
      bx[shot_count] = player_x+16;
      by[shot_count] = player_y+1;
      shot_count++;
      if(shot_count > 20) shot_count= 0;
      countdown = 30;
    }
  }
  if (countdown != 0){
    countdown--;
  }
  if (arduboy.pressed(A_BUTTON) && bomb_num != 0 && bomb_countdown == 0){
    bomb_countdown = 120;
    timeGo = false;
    bomb_num--;
  }

  if (bomb_countdown != 0){
      bomb_countdown--;
  }
  else{
    timeGo = true;
  }
}

void check_player_bullets(){
  for (int i = 0; i <= 20; i++){
    if (bx[i] != NULL && by[i] != NULL){
      for (int e = 0; e <= 19; e++){
        if ((bx[i] >= enemy_arr[e].x && bx[i] <= enemy_arr[e].x+enemy_arr[e].width
        && by[i] >= enemy_arr[e].y && by[i] <= enemy_arr[e].y+enemy_arr[e].height)
        ||(bx[i]+8 >= enemy_arr[e].x && bx[i]+8 <= enemy_arr[e].x+enemy_arr[e].width
        && by[i]+8 >= enemy_arr[e].y && by[i]+8 <= enemy_arr[e].y+enemy_arr[e].height)){
          enemy_arr[e].HP--;
          bx[i] = NULL;
          by[i] = NULL;
        }
      }
      if (bx[i] > X_MAX + 8){
        bx[i] = NULL;
        by[i] = NULL;
      }
      else{
        arduboy.drawBitmap(bx[i],by[i],shot,8,8,WHITE);
        bx[i]++;
      }
    }
  }
}

void player_death_stuff(){
  player_is_alive = false;
  score = 0;
  death_countdown = 60;
  gameBegun = 0;
  enemy_count = 0;
  enemy_countdown = enemy_countdown_initial;
  player_x = 0;
  player_y = (HEIGHT / 2);
  player_last_HP = player_HP;
  player_inv_countdown = 0;
  bomb_num = 3;
  for (int i=0; i <= 19; i++){
    enemy_arr[i].death_stuff();
  }
}

void check_player_HP(){
  if (player_HP <= 0){
    player_death_stuff();
  }
}



void check_player_invincibility(){
  if (player_inv_countdown > 0 ){
    player_inv_countdown--;
    player_HP = player_last_HP;
  }
}

void player_animation(){
  if (player_inv_countdown != 0){
    if (framecount<15){
      arduboy.drawBitmap(player_x,player_y,shipwhole,16,8,WHITE);
    }
    else if ((framecount>=30 && framecount<45))  {
      arduboy.drawBitmap(player_x,player_y,shipwhole1,16,8,WHITE);
    }
    else if ((framecount >=15 && framecount<30) || (framecount >=45)){
      //do nothing, blank sprite.
    }
  }
  else{
    if (framecount<15 || (framecount>=30 && framecount<45)){
      arduboy.drawBitmap(player_x,player_y,shipwhole,16,8,WHITE);
    }
    
    else if ((framecount>=15 && framecount<30) || framecount>=45)  {
      arduboy.drawBitmap(player_x,player_y,shipwhole1,16,8,WHITE);
    }
  }
  framecount++;
  if (framecount > 59){framecount =0;}
}

void player_update(){
  if (player_is_alive ==false) return;
  check_player_invincibility();
  check_player_HP();
  check_player_buttons();
  check_player_bullets();
  player_animation();
}


