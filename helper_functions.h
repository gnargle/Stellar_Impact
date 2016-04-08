void debug(char* debug_text, int x, int y){
  //max size 21
  arduboy.setCursor(x,y);
  arduboy.print(debug_text);  
}

void create_enemies(){
  if (!timeGo)return;
  if (enemy_countdown == 0){
      if (enemy_count <= 19){
        if (enemy_arr[enemy_count+1].isEnemy == false){
          Enemy newenemy;
          newenemy.isEnemy = true;
          newenemy.on_spawn();
          enemy_arr[enemy_count + 1] = newenemy;
        }
        enemy_count +=1;
      }
      if (enemy_count > 19) enemy_count = 0;
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
  if (star_countdown_depth == 0){
    star_create_depth(1);
    star_countdown_depth = star_countdown_initial_depth;
  }
  if (star_countdown_depth1 == 0){
    star_create_depth(2);
    star_countdown_depth1 = 2*star_countdown_initial_depth;
  }
  if (star_countdown_depth2 == 0){
    star_create_depth(3);
    star_countdown_depth = 3*star_countdown_initial_depth;
  }
  star_countdown_depth--;
  star_countdown_depth1--;
  star_countdown_depth2--;
}

void star_create_gamestart(){
  for (int i = 0; i <= 30; i++){
    Star newstar;
    newstar.star_exists = true;
    newstar.depth = random(1,3);
    newstar.x = random(1,WIDTH);
    starfield_arr[i] = newstar;
  }
}

