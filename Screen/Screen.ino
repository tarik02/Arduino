#include "LCD.h"
//#include "3D.h"

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

//Object3D Shape(12,6);

static unsigned char PROGMEM ball[] =
{
  B00010000,
  B00111000,
  B01111100,
  B11111110,
  B01111100,
  B00111000,
  B00010000
};

int8_t player1pos,player2pos;
int8_t ballX = 38,ballY = 20;
int8_t ballAngle = 0;


bool Game = true;
bool Res = false;

void newGame()
{
  player1pos = player2pos = 20;
  ballX = 38;
  ballY = 20;
  ballAngle = random(4);
  Screen->clear();
  Game = true;
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
  /*
  Screen->drawHLine(0,7,83,true);
  Screen->drawHLine(0,8,83,true);
  
  Screen->drawChar(0,0,'H',true);
  Screen->drawChar(6,0,'E',true);
  Screen->drawChar(12,0,'L',true);
  Screen->drawChar(18,0,'L',true);
  Screen->drawChar(24,0,'O',true);
  Screen->drawChar(30,0,' ',true);
  Screen->drawChar(36,0,'W',true);
  Screen->drawChar(42,0,'O',true);
  Screen->drawChar(48,0,'R',true);
  Screen->drawChar(54,0,'L',true);
  Screen->drawChar(60,0,'D',true);
  Screen->drawChar(66,0,'!',true);
  Screen->drawChar(72,0,'!',true);
  Screen->drawChar(78,0,'!',true);
  */
  /*
  Shape.Vertices[0] = Vertex(-100,-100,0);
  Shape.Vertices[1] = Vertex(-100,100,0);
  Shape.Vertices[2] = Vertex(100,100,0);
  Shape.Vertices[3] = Vertex(100,-100,0);
  Shape.Vertices[4] = Vertex(0,0,-141.42);
  Shape.Vertices[5] = Vertex(0,0,141.42);
  
  Shape.Edges[0] = Edge(0,1);
  Shape.Edges[1] = Edge(1,2);
  Shape.Edges[2] = Edge(2,3);
  Shape.Edges[3] = Edge(3,0);
  Shape.Edges[4] = Edge(4,0);
  Shape.Edges[5] = Edge(4,1);
  Shape.Edges[6] = Edge(4,2);
  Shape.Edges[7] = Edge(4,3);
  Shape.Edges[8] = Edge(5,0);
  Shape.Edges[9] = Edge(5,1);
  Shape.Edges[10] = Edge(5,2);
  Shape.Edges[11] = Edge(5,3);
  
  Shape.x = 0;
  Shape.y = 0;
  Shape.z = 200;
  
  Screen->clear();
  RotateShape(Shape,0.01,0.05,0.08);
  ShowShape(Screen,Shape);
  */
  //Screen->drawFillRect(37,19,47,29,true);
  newGame();
}

void loop()
{
  if (digitalRead(BUTTON1) == HIGH)
  {
    //while (digitalRead(BUTTON1) != LOW);
    //RotateShape(Shape,0.01,0,0);
    player1pos = ((player1pos - 3) > 0) ? (player1pos - 3) : 0;
  };
  if (digitalRead(BUTTON2) == HIGH)
  {
    //while (digitalRead(BUTTON2) != LOW);
    //RotateShape(Shape,0,0.01,0);
    player2pos = ((player2pos - 3) > 0) ? (player2pos - 3) : 0;
  };
  if (digitalRead(BUTTON3) == HIGH)
  {
    //while (digitalRead(BUTTON3) != LOW);
    if (!Game)
      newGame();
  };
  if (digitalRead(BUTTON4) == HIGH)
  {
    //while (digitalRead(BUTTON4) != LOW);
    //RotateShape(Shape,0,-0.01,0);
    player2pos = ((player2pos + 3) < 32) ? (player2pos + 3) : 32;
  };
  if (digitalRead(BUTTON5) == HIGH)
  {
    //while (digitalRead(BUTTON5) != LOW);
    //RotateShape(Shape,-0.01,0,0);
    player1pos = ((player1pos + 3) < 32) ? (player1pos + 3) : 32;
  };
  if (digitalRead(BUTTON6) == HIGH)
  {
    //while (digitalRead(BUTTON6) != LOW);
  };
  
  
  //RotateShape(Shape,0.01,0.05,0.08);
  //Screen->clear();
  //ShowShape(Screen,Shape);
  
  Screen->clear();
  
  if (Game)
  {
    switch (ballAngle)
    {
      case 0:
      ballX += 3;
      ballY += 3;
      break;
      case 1:
      ballX -= 3;
      ballY += 3;
      break;
      case 2:
      ballX -= 3;
      ballY -= 3;
      break;
      case 3:
      ballX += 3;
      ballY -= 3;
      break;
    };
    
    if (ballY <= 1)
    {
      switch (ballAngle) { case 2: ballAngle = 1; break; case 3: ballAngle = 0; break; };
    }
    else if (ballY >= 39)
    {
      switch (ballAngle) { case 0: ballAngle = 3; break; case 1: ballAngle = 2; break; };
    };
    
    if (ballX <= 5)
    {
      if ((player1pos <= ballY) && (player1pos + 16 >= ballY))
      {
        switch (ballAngle) { case 1: ballAngle = 0; break; case 2: ballAngle = 3; break; };
      }
      else
      {
        Res = false;
        Game = false;
      };
    }
    else if (ballX >= 71)
    {
      if ((player2pos <= ballY) && (player2pos + 16 >= ballY))
      {
        switch (ballAngle) { case 0: ballAngle = 1; break; case 3: ballAngle = 2; break; };
      }
      else
      {
        Res = true;
        Game = false;
      };
    };
    
    Screen->drawFillRect(1,player1pos,4,player1pos + 16);
    Screen->drawFillRect(79,player2pos,82,player2pos + 16);
    Screen->drawBitmap(ballX,ballY,7,7,ball);
    
    Screen->drawRect(0,0,83,47);
  }
  else
  {
    if (Res)
    {
      Screen->drawText(3,1,"Player 1 Win!");
    }
    else
    {
      Screen->drawText(3,1,"Player 2 Win!");
    };
    
    Screen->drawHLine(0,9,83);
    
    Screen->drawText(0,11,"Press ");
    Screen->drawBitmap(36,11,7,7,ball);
    Screen->drawText(44,11," to pl-");
    Screen->drawText(18,19,"ay again");
  };
  
  Screen->display();
    
  delay(100);
}






