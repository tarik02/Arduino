#include "Program.h"
#include "API.h"
#include "s3DTest.h"
#include "Timer.h"

// Edges count
// Vertices count

void T3DTest_Timer(void *Data)
{
  RotateShape(((T3DTest *)Data)->Shape,0.005,0.005,0.005);
};

T3DTest::T3DTest() : TProgram(true)
{
  icon = (unsigned char *)T3DTestIcon;
  
  addTimer(1,false,T3DTest_Timer,this);
  /*
  Shape = new TObject3D(6,12,25);
  
  Shape->x = 0;
  Shape->y = 0;
  Shape->z = 200;
  
  Shape->vertices[0].x = -100; Shape->vertices[0].y = -100; Shape->vertices[0].z = 0;
  Shape->vertices[1].x = -100; Shape->vertices[1].y =  100; Shape->vertices[1].z = 0;
  Shape->vertices[2].x =  100; Shape->vertices[2].y =  100; Shape->vertices[2].z = 0;
  Shape->vertices[3].x =  100; Shape->vertices[3].y = -100; Shape->vertices[3].z = 0;
  Shape->vertices[4].x =  0;   Shape->vertices[4].y =  0;   Shape->vertices[4].z = -141.42;
  Shape->vertices[5].x =  0;   Shape->vertices[5].y =  0;   Shape->vertices[5].z =  141.42;
  
  Shape->edges[0].src  = 0; Shape->edges[0].dst  = 1;
  Shape->edges[1].src  = 1; Shape->edges[1].dst  = 2;
  Shape->edges[2].src  = 2; Shape->edges[2].dst  = 3;
  Shape->edges[3].src  = 3; Shape->edges[3].dst  = 0;
  Shape->edges[4].src  = 4; Shape->edges[4].dst  = 0;
  Shape->edges[5].src  = 4; Shape->edges[5].dst  = 1;
  Shape->edges[6].src  = 4; Shape->edges[6].dst  = 2;
  Shape->edges[7].src  = 4; Shape->edges[7].dst  = 3;
  Shape->edges[8].src  = 5; Shape->edges[8].dst  = 0;
  Shape->edges[9].src  = 5; Shape->edges[9].dst  = 1;
  Shape->edges[10].src = 5; Shape->edges[10].dst = 2;
  Shape->edges[11].src = 5; Shape->edges[11].dst = 3;
  */
  Shape = new TObject3D(8,12,300);
  
  Shape->x = 0;
  Shape->y = 0;
  Shape->z = 200;
  
  Shape->vertices[0].x = -10; Shape->vertices[0].y = -10; Shape->vertices[0].z = -10;
  Shape->vertices[1].x = -10; Shape->vertices[1].y = -10; Shape->vertices[1].z =  10;
  Shape->vertices[2].x =  10; Shape->vertices[2].y = -10; Shape->vertices[2].z =  10;
  Shape->vertices[3].x =  10; Shape->vertices[3].y = -10; Shape->vertices[3].z = -10;
  Shape->vertices[4].x = -10; Shape->vertices[4].y =  10; Shape->vertices[4].z = -10;
  Shape->vertices[5].x = -10; Shape->vertices[5].y =  10; Shape->vertices[5].z =  10;
  Shape->vertices[6].x =  10; Shape->vertices[6].y =  10; Shape->vertices[6].z =  10;
  Shape->vertices[7].x =  10; Shape->vertices[7].y =  10; Shape->vertices[7].z = -10;
  //Shape->vertices[8].x =  50;  Shape->vertices[8].y =  75;   Shape->vertices[8].z =  25;
  
  Shape->edges[0].src  = 0; Shape->edges[0].dst  = 1;
  Shape->edges[1].src  = 0; Shape->edges[1].dst  = 3;
  Shape->edges[2].src  = 0; Shape->edges[2].dst  = 4;
  
  Shape->edges[3].src  = 2; Shape->edges[3].dst  = 1;
  Shape->edges[4].src  = 2; Shape->edges[4].dst  = 3;
  Shape->edges[5].src  = 2; Shape->edges[5].dst  = 6;
  
  Shape->edges[6].src  = 5; Shape->edges[6].dst  = 1;
  Shape->edges[7].src  = 5; Shape->edges[7].dst  = 4;
  Shape->edges[8].src  = 5; Shape->edges[8].dst  = 6;
  
  Shape->edges[9].src  = 7; Shape->edges[9].dst  = 3;
  Shape->edges[10].src = 7; Shape->edges[10].dst = 4;
  Shape->edges[11].src = 7; Shape->edges[11].dst = 6;
  
  RotateShape(Shape,0,0.785,0);
  //RotateShape(Shape,0.785,0.785,0.785);
  
  //RotateShape(Shape,0,PI * random(360) / 180,0);
  // PI * a / 180
};
void T3DTest::Start()
{
  
};
void T3DTest::ReadButtons(byte &Buttons)
{
  if ((Buttons | _BV(2)) == Buttons)
  {
    RotateShape(Shape,0,0.01,0);
  }
  if ((Buttons | _BV(4)) == Buttons)
  {
    RotateShape(Shape,0,-0.01,0);
  }
  if ((Buttons | _BV(1)) == Buttons)
  {
    //RotateShape(Shape,0.01,0,0);
    Shape->z -= 0.25;
  }
  if ((Buttons | _BV(5)) == Buttons)
  {
    //RotateShape(Shape,-0.01,0,0);
    Shape->z += 0.25;
  }
};
void T3DTest::Paint(LCD *Canvas)
{
  ShowShape(Shape,Canvas);
};
