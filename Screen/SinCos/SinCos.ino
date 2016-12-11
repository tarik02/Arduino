#include "LCD.h"
#include "SinCosLib.h"

#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4
#define BUTTON6 5

#define S_RST 12
#define S_CE  11
#define S_DC  10
#define S_DIN  9
#define S_CLK  8

LCD *Screen;

int sec;

typedef float Point[2];

void setup()
{
  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);
  pinMode(BUTTON4,INPUT);
  pinMode(BUTTON5,INPUT);
  pinMode(BUTTON6,INPUT);
  
  Screen = new LCD(S_RST,S_CE,S_DC,S_DIN,S_CLK);
  Screen->clear();
}

void loop()
{
  Screen->clear();
  
  Screen->drawLine(42,24,42 + myCos(sec) * 20,24 + mySin(sec) * 20);
  
  Screen->display();
  
  sec++;
  if (sec == 360)
    sec = 0;
  
  delay(1000);
}






