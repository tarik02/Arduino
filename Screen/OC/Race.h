#ifndef _PROGRAM_RACE_
#define _PROGRAM_RACE_
#include <Arduino.h>

static const unsigned char RaceIcon[] PROGMEM =
{
  B00000000,  B00000000,  B00000000,
  B00000000,  B00000000,  B00000000,
  B00111011,  B01111000,  B00000000,
  B00101111,  B11000100,  B00000000,
  B00010000,  B00000010,  B00000000,
  B00011000,  B00000001,  B00000000,
  B00011000,  B00000001,  B00000000,
  B00010000,  B00000010,  B00000000,
  B00101111,  B11000100,  B00000000,
  B00111011,  B01111000,  B00000000,
  B00000000,  B00000000,  B00000000,
  B00000000,  B00000000,  B00000000,
};

static const unsigned char MachineImage1[] PROGMEM =
{
  B00000000,  B00000000,
  B00000110,  B00000000,
  B00001001,  B00000000,
  B00010000,  B10000000,
  B00100000,  B01000000,
  B00100000,  B01000000,
  B00100000,  B01000000,
  B00110000,  B11000000,
  B00010000,  B10000000,
  B00110000,  B11000000,
  B00110000,  B11000000,
  B00010000,  B10000000,
  B00110110,  B11000000,
  B00101111,  B01000000,
  B00110000,  B11000000,
  B00000000,  B00000000,
  B00000000,  B00000000,
};
static const unsigned char MachineImage2[] PROGMEM =
{
  B00000000,  B00000000,
  B00000000,  B00000000,
  B00110000,  B11000000,
  B00101111,  B01000000,
  B00110110,  B11000000,
  B00010000,  B10000000,
  B00110000,  B11000000,
  B00110000,  B11000000,
  B00010000,  B10000000,
  B00110000,  B11000000,
  B00100000,  B01000000,
  B00100000,  B01000000,
  B00100000,  B01000000,
  B00010000,  B10000000,
  B00001001,  B00000000,
  B00000110,  B00000000,
  B00000000,  B00000000,
};

class TMachine
{
  private:
  public:
  
  int X,Y;
};

class TRace : public TProgram
{
  friend void TRaceTimer(void *Data);
  private:
  TMachine Machines[5];
  
  int myX,myY;
  
  int destX;
  public:
  TRace();
  
  void Start();
  void ReadButtons(byte &Buttons);
  void Paint(LCD *Canvas);
};
#endif

