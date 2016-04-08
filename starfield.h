
class Star{
  public:
    byte depth = 1;
    byte depth_countdown;
    byte x = 127;
    byte y = random(0, HEIGHT);
    bool star_exists = true;

    void position_update(){
      if (x == 0) star_exists = false;
      if (arduboy.everyXFrames(depth) && timeGo){
        x--;
      }
    }

    void star_draw(){
      if (star_exists){
        arduboy.drawPixel(x,y,WHITE);
      }
    }

    void star_update(){
      star_draw();
      position_update();
    }
};

void starfield_update(Star* star_arr){
  for (int i = 0; i <=29; i++){
    if (star_arr[i].star_exists == true){
      star_arr[i].star_update();
    }
  }
}

