#ifndef _PROGRAM_TESTING_
#define _PROGRAM_TESTING_
#include <Arduino.h>
#include "Sounds.h"

static int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
static int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

static const unsigned char TestingIcon[] PROGMEM =
{
  B11111111,  B11111111,  B10000000,
  B10001000,  B10001000,  B10000000,
  B11011011,  B10111101,  B10000000,
  B11011000,  B10001101,  B10000000,
  B11011011,  B11101101,  B10000000,
  B11011000,  B10001101,  B10000000,
  B11111111,  B11111111,  B10000000,
  B11010110,  B10001111,  B10000000,
  B11110010,  B10111111,  B10000000,
  B11010100,  B10101111,  B10000000,
  B11010110,  B10001111,  B10000000,
  B11111111,  B11111111,  B10000000,
};

class TTesting : public TProgram
{
  friend void TTestingTimer(void *Data);
  private:
  int ballX,ballY;
  double rot;
  //int gr;
  
  TSounds *Sounds;
  TSound *Sound;
  public:
  TTesting();
  
  void Start();
  void ReadButtons(byte &Buttons);
  void Paint(LCD *Canvas);
};
#endif

