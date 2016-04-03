void debug(char* debug_text, int x, int y){
  //max size 21
  arduboy.setCursor(x,y);
  arduboy.print(debug_text);  
}

void create_enemies(){
  if (arduboy.everyXFrames(60)){
      if (enemy_count < 19){
        if (enemy_arr[enemy_count+1].isEnemy == false){
          Enemy newenemy;
          newenemy.isEnemy = true;
          enemy_arr[enemy_count + 1] = newenemy;
        }
        enemy_count +=1;
      }
      if (enemy_count >= 19) enemy_count = 0;
    }
}
