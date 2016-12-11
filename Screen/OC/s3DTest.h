#ifndef _PROGRAM_3DTEST_
#define _PROGRAM_3DTEST_
#include <Arduino.h>
#include "lib3D.h"

static const unsigned char T3DTestIcon[] PROGMEM =
{
  B11111111,  B10000000,  B00000000,
  B11000001,  B10111100,  B00000000,
  B11000001,  B10111110,  B00000000,
  B11111001,  B10110111,  B00000000,
  B11111001,  B10110011,  B00000000,
  B11000001,  B10110011,  B00000000,
  B11000001,  B10110011,  B00000000,
  B11111001,  B10110011,  B00000000,
  B11111001,  B10110111,  B00000000,
  B11000001,  B10111110,  B00000000,
  B11000001,  B10111100,  B00000000,
  B11111111,  B10000000,  B00000000,
};

class T3DTest : public TProgram
{
  friend void T3DTest_Timer(void *Data);
  private:
  TObject3D *Shape;
  public:
  T3DTest();
  
  void Start();
  void ReadButtons(byte &Buttons);
  void Paint(LCD *Canvas);
};
#endif

