#include "Timer.h"
#include "Program.h"
#include "flappyBird.h"

void TFlappyBirdonWorkTimer(void *Data)
{
  if (((TFlappyBird *)Data)->doOver)
  {
    if (((TFlappyBird *)Data)->y > 36)
      ((TFlappyBird *)Data)->y--;
    else if (((TFlappyBird *)Data)->y < 36)
      ((TFlappyBird *)Data)->y++;
    
    ((TFlappyBird *)Data)->doOver = false;
    
    for (int i = 0; i < 2; i++)
    {
      ((TFlappyBird *)Data)->Walls[i].Position += 2;
      
      if (((TFlappyBird *)Data)->Walls[i].Position < 29)
        ((TFlappyBird *)Data)->doOver = true;
    };
    
    return;
  };
  
  if (!((TFlappyBird *)Data)->Playing) { return; }
  
  ((TFlappyBird *)Data)->y--;
  
  for (int i = 0; i < 2; i++)
  {
    ((TFlappyBird *)Data)->Walls[i].Position--;
    
    if (((TFlappyBird *)Data)->Walls[i].Position <= -29)
    {
      ((TFlappyBird *)Data)->Walls[i].Position = 29;
      ((TFlappyBird *)Data)->Walls[i].Value = -15 + random(30);
    }
  }
  
  if (((TFlappyBird *)Data)->birdJump > 0)
  {
    ((TFlappyBird *)Data)->y += ((TFlappyBird *)Data)->birdJump;
    ((TFlappyBird *)Data)->birdJump--;
  }
  
  if (((TFlappyBird *)Data)->y <= 0)
  {
    ((TFlappyBird *)Data)->Playing = false;
    ((TFlappyBird *)Data)->doOver = true;
  }
  
  for (int i = 0; i < 2; i++)
  {
    if ((((TFlappyBird *)Data)->Walls[i].Position > -5) &&
        (((TFlappyBird *)Data)->Walls[i].Position < 5))
    {
      if ((27 + ((TFlappyBird *)Data)->Walls[i].Value > ((TFlappyBird *)Data)->y) ||
          (57 + ((TFlappyBird *)Data)->Walls[i].Value - 12 < ((TFlappyBird *)Data)->y))
      {
        ((TFlappyBird *)Data)->Playing = false;
        ((TFlappyBird *)Data)->doOver = true;
      };
    };
    
  };
};

TFlappyBird::TFlappyBird() : TProgram(true)
{
  icon = (unsigned char *)FlappyBirdIcon;
  
  WorkTimer = addTimer(50,false,TFlappyBirdonWorkTimer,this);
  Playing = true;
};
void TFlappyBird::Start()
{
  StartGame();
};
void TFlappyBird::ReadButtons(byte &Buttons)
{
  if ((Buttons | _BV(3)) == Buttons)
  {
    Buttons &= ~_BV(3);
    
    if (Playing)
      //y += 5;
      birdJump = 4;
    else
      StartGame();
  }
};
void TFlappyBird::Paint(LCD *Canvas)
{
  if (millis() % 125 > 50)
    Canvas->drawBitmapPGM(y,18,12,16,flappybird_frame_1);
  else
    Canvas->drawBitmapPGM(y,18,12,16,flappybird_frame_2);
  
  if (Playing || doOver)
  {
    for (int i = 0; i < 2; i++)
    {
      Canvas->drawFillRect(0,24 + Walls[i].Position,27 + Walls[i].Value,24 + Walls[i].Position + 5);
      Canvas->drawFillRect(24 + Walls[i].Value,22 + Walls[i].Position,27 + Walls[i].Value,26 + Walls[i].Position + 5);
      
      Canvas->drawFillRect(57 + Walls[i].Value,24 + Walls[i].Position,84,24 + Walls[i].Position + 5);
      Canvas->drawFillRect(60 + Walls[i].Value,22 + Walls[i].Position,57 + Walls[i].Value,26 + Walls[i].Position + 5);
    }
  }
  else
  {
    
  };
};
void TFlappyBird::StartGame()
{
  y = 36;
  Playing = true;
  doOver = false;
  
  Walls[0].Value = 0;
  Walls[0].Position = 29;
  
  Walls[1].Value = 5;
  Walls[1].Position = 29 * 2;
};

