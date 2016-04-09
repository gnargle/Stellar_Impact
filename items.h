#define HEART false
#define BOMB true

class Item{
  public:
    byte x = 0;
    byte y = 0;
    byte movement_rate = 1;
    bool itemType;
    bool isItem = false;

  void draw_item(){
    if (!isItem) return;
    if(itemType == HEART){
      arduboy.drawBitmap(x,y,heart,8,8,WHITE);
    }
    else if (itemType == BOMB){
      arduboy.drawBitmap(x,y,bomb,8,8,WHITE);
    }
  }

  void update_item_position(){
    if(!isItem) return;
    if(arduboy.everyXFrames(movement_rate && timeGo)){
      x--;
    }
    if (x==0) isItem = false;
  }

  void item_update(){
    update_item_position();
    draw_item();
  }
};

void item_arr_update(Item* item_arr){
  for(int i = 0; i<=5;i++){
    if(item_arr[i].isItem){
      item_arr[i].item_update();
    }
  }
}

Item item_arr[6];
