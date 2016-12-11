#include "LCD.h"

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

Point coords[] =
{
  {-0.994359788416093,0.106059470020847},
  {-0.977837464303335,0.209365454181973},
  {-0.950612598102916,0.310379909672041},
  {-0.912983169066988,0.407997221804756},
  {-0.865361035569458,0.501148958013638},
  {-0.80826742726931,0.588815561967795},
  {-0.742327240192802,0.670037512731741},
  {-0.668262197175495,0.743925826830995},
  {-0.58688294852386,0.809671788277164},
  {-0.49908019935562,0.866555800056265},
  {-0.405814960731091,0.913955260199767},
  {-0.308108031277993,0.951351376233829},
  {-0.207028824434553,0.978334843421846},
  {-0.103683663597983,0.994610324651268},
  {0.000796326710733041,0.999999682931835},
};

float myCos(int angle)
{
  angle /= 6;
  if (angle < 15)
  {
    return coords[angle][0];
  }
  if (angle < 29)
  {
    return -coords[28 - angle][0];
  }
  if (angle < 45)
  {
    return -coords[angle - 29][0];
  }
  if (angle < 60)
  {
    return coords[angle - 45][0];
  }
};
float mySin(int angle)
{
  angle /= 6;
  if (angle < 15)
  {
    return coords[angle][1];
  }
  if (angle < 29)
  {
    return coords[28 - angle][1];
  }
  if (angle < 45)
  {
    return -coords[angle - 29][1];
  }
  if (angle < 60)
  {
    return coords[angle - 45][1];
  }
};

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
  
  Screen->drawLine(42,24,42 + mySin(sec * 6) * 20,24 + myCos(sec * 6) * 20);
  
  Screen->display();
  
  sec++;
  if (sec == 45)
    sec = 0;
  
  delay(100);
}






