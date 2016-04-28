Arduboy arduboy;
ArduboyAudio audio;
ArduboyTunes tune;
bool audio_enabled;
byte audio_countdown = 0;

byte led_countdown;
byte which_led = 0;

byte secret[8];
byte secret_tracker = 0;

byte enemy_count = 0;
byte max_enemies = 9;
byte enemy_countdown_initial = 60;
byte enemy_countdown = enemy_countdown_initial;
byte last_enem_spr = 0;
short med_countdown = 1200;
short big_countdown = 2400;
short boss_countdown = 3600;
bool boss_on_screen = false;

byte star_count = 0;
byte star_countdown_initial_depth = 6;
byte star_countdown_depth = star_countdown_initial_depth;

byte player_x;
byte player_y;
byte player_HP = 3;
byte player_last_HP = player_HP;
byte player_inv_countdown = 0;
bool player_last_spr;
byte invincibility_length = 120;
byte death_countdown = 60;
boolean player_is_alive = true;
byte countdown = 30;
byte bomb_countdown = 0;
byte bomb_num = 3;
byte bomb_rad = 0;
byte bomb_x;
byte bomb_y;
byte shot_count = 0;
byte bx[17];
byte by[17];

boolean gameBegun = false;
boolean gamePaused = false;
byte pause_countdown = 0;
boolean score_recorded = false;
byte framecount = 0;

bool timeGo = true;
short score = 0;
short high_score;
