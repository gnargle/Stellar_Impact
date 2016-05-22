#define HIGHSCORE_INIT 10

#define EEPROM_HEADER_LENGTH 15
#define EEPROM_HEADER_START 40
#define EEPROM_START (EEPROM_HEADER_START + EEPROM_HEADER_LENGTH)

const char EepromHeader[EEPROM_HEADER_LENGTH] = "Stellar_Impact";

byte read_EEPROM(int offset){
  byte val;
  val = EEPROM.read(EEPROM_START + offset);
  return val;
}

void write_EEPROM(int offset, int val){
  EEPROM.update(EEPROM_START + offset, val);
}

void validate_EEPROM() {
  bool headerCorrect = true;
  for (int i = EEPROM_HEADER_START; i < EEPROM_START; i++) {
    if(EEPROM.read(EEPROM_HEADER_START + i) != EepromHeader[i]) {
      headerCorrect = false;
      break;
    }
  }

  if (!headerCorrect) {
    // write EEPROM header
    for (int i = EEPROM_HEADER_START; i < EEPROM_START; i++) {
      EEPROM.update(EEPROM_HEADER_START + i, EepromHeader[i]);
    }
    
    write_EEPROM(1, HIGHSCORE_INIT);
    write_EEPROM(0, 0);
  }
}

short read_High_Score(){
  // score should be 2 bytes long since we're using a short
  // we will use bytes 54 and 55
  //byte 54 is high byte, byte 55 is low byte
  byte val;
  byte val1;
  short hs;

  validate_EEPROM();
  val = read_EEPROM(0);
  val1 = read_EEPROM(1);
  
  //by this point, we have a 2 value array containing the high and low bytes of high score.
  //so we or them together with the high byte bitshifted to create a high score short
  hs = (val << 8) | val1;
  
  return hs;
}

void write_High_Score(){
  if (score > high_score){
    byte val;
    byte val1;
    val = score & 0xFF; // get low byte of score
    write_EEPROM(1,val);
    val1 = (score >> 8) & 0xFF; // get high byte of score
    write_EEPROM(0,val1);
  }
}

