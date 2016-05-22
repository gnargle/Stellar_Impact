#define HIGHSCORE_INIT 10

#define EEPROM_HEADER_LENGTH 15
#define EEPROM_HEADER_START 39
#define EEPROM_START (EEPROM_HEADER_START + EEPROM_HEADER_LENGTH)

const char EepromHeader[EEPROM_HEADER_LENGTH] = "Stellar_Impact";

byte read_EEPROM(int offset){
  byte val;
  val = EEPROM.read(EEPROM_START + offset);
  return val;
}

void write_EEPROM(int offset, byte val){
  EEPROM.update(EEPROM_START + offset, val);
}

void reset_EEPROM() {
  for (int i = EEPROM_HEADER_START; i < EEPROM_START; i++) {
    EEPROM.update(EEPROM_HEADER_START + i, EepromHeader[i]);
  }

  write_EEPROM(2, HIGHSCORE_INIT);
  write_EEPROM(1, HIGHSCORE_INIT);
  write_EEPROM(0, 0);
}

void validate_EEPROM() {
  bool headerCorrect = true;
  for (int i = EEPROM_HEADER_START; i < EEPROM_START; i++) {
    if(EEPROM.read(EEPROM_HEADER_START + i) != EepromHeader[i]) {
      headerCorrect = false;
      break;
    }
  }

  if (headerCorrect) {
    byte valHigh = read_EEPROM(0);
    byte valLow = read_EEPROM(1);
    byte checksum = read_EEPROM(2);
    byte expected = valHigh ^ valLow;
    if(checksum != expected) {
      Serial.print("Read wrong: ");
      Serial.print(checksum, HEX);
      Serial.print(" ");
      Serial.println(expected, HEX);
      headerCorrect = false;
    }
  }

  if (!headerCorrect) {
    reset_EEPROM();
  }
}

short read_High_Score(){
  // score should be 2 bytes long since we're using a short
  byte valHigh;
  byte valLow;
  short hs;

  validate_EEPROM();
  valHigh = read_EEPROM(0);
  valLow = read_EEPROM(1);
  
  //by this point, we have a 2 value array containing the high and low bytes of high score.
  //so we or them together with the high byte bitshifted to create a high score short
  hs = (valHigh << 8) | valLow;
  
  return hs;
}

void write_High_Score(){
  if (score > high_score){
    byte valHigh;
    byte valLow;
    byte checksum;
    
    valHigh = (score >> 8) & 0xFF;
    write_EEPROM(0,valHigh);
    
    valLow = score & 0xFF;
    write_EEPROM(1,valLow);
    
    checksum = valHigh ^ valLow;
    write_EEPROM(2,checksum);
      Serial.print("Wrote: ");
      Serial.println(checksum, HEX);
  }
}

