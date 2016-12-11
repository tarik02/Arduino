#include "lib3D.h"

void MMMult(Matrix lhs,Matrix rhs,Matrix &r)
{
  uint8_t i,j,k;
  float s;
  
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
    {
      s = 0;
      for (k = 0; k < 4; k++)
        s = s + lhs[i][k] * rhs[k][j];
      r[i][j] = s;
    };
};
void MCMult(Matrix lhs,Column rhs,Column &r)
{
  uint8_t i,k;
  float s;
  
  for (i = 0; i < 4; i++)
  {
    s = 0;
    for (k = 0; k < 4; k++)
      s = s + lhs[i][k] * rhs[k];
    r[i] = s;
  };
};

void RotateMatrix(float xa,float ya,float za,Matrix &r)
{
  Matrix xr,yr,zr;
  
  xr[0][0] = 1; xr[0][1] = 0;       xr[0][2] = 0;        xr[0][3] = 0;
  xr[1][0] = 0; xr[1][1] = cos(xa); xr[1][2] = -sin(xa); xr[1][3] = 0;
  xr[2][0] = 0; xr[2][1] = sin(xa); xr[2][2] = cos(xa);  xr[2][3] = 0;
  xr[3][0] = 0; xr[3][1] = 0;       xr[3][2] = 0;        xr[3][3] = 1;
  
  yr[0][0] = cos(ya);  yr[0][1] = 0; yr[0][2] = sin(ya); yr[0][3] = 0;
  yr[1][0] = 0;        yr[1][1] = 1; yr[1][2] = 0;       yr[1][3] = 0;
  yr[2][0] = -sin(ya); yr[2][1] = 0; yr[2][2] = cos(ya); yr[2][3] = 0;
  yr[3][0] = 0;        yr[3][1] = 0; yr[3][2] = 0;       yr[3][3] = 1;
  
  zr[0][0] = cos(za); zr[0][1] = -sin(za); zr[0][2] = 0; zr[0][3] = 0;
  zr[1][0] = sin(za); zr[1][1] = cos(za);  zr[1][2] = 0; zr[1][3] = 0;
  zr[2][0] = 0;       zr[2][1] = 0;        zr[2][2] = 1; zr[2][3] = 0;
  zr[3][0] = 0;       zr[3][1] = 0;        zr[3][2] = 0; zr[3][3] = 1;
  
  MMMult(xr,yr,r);
  MMMult(r,zr,r);
};

float Max(float a,float b)
{
  if (a > b)
    return a;
  return b;
};

void RotateShape(TObject3D *Shape,float xa,float ya,float za)
{
  Matrix rm;
  Column c,c2;
  
  RotateMatrix(xa,ya,za,rm);
  c[3] = 1;
  
  int i,j;
  
  for (i = 0; i < Shape->verticesCount; i++)
  {
    c[0] = Shape->vertices[i].x;
    c[1] = Shape->vertices[i].y;
    c[2] = Shape->vertices[i].z;
    
    MCMult(rm,c,c);
      
    Shape->vertices[i].x = c[0];
    Shape->vertices[i].y = c[1];
    Shape->vertices[i].z = c[2];
  };
};
void ShowShape(TObject3D *Shape,LCD *Canvas)
{
  uint8_t i,sX,sY,dX,dY;
  float x,y,z;
  
  for (i = 0; i < Shape->edgesCount; i++)
  {
    x = Shape->vertices[Shape->edges[i].src].x + Shape->x;
    y = Shape->vertices[Shape->edges[i].src].y + Shape->y;
    z = Shape->vertices[Shape->edges[i].src].z + Shape->z;
    
    if (abs(z) < 0.01) { z = 0.01; };
    
    sX = (84 / 2) + (Shape->perspective * x / z);
    sY = (48 / 2) + (Shape->perspective * y / z);
    
    
    x = Shape->vertices[Shape->edges[i].dst].x + Shape->x;
    y = Shape->vertices[Shape->edges[i].dst].y + Shape->y;
    z = Shape->vertices[Shape->edges[i].dst].z + Shape->z;
    
    if (abs(z) < 0.01) { z = 0.01; };
    
    dX = (84 / 2) + (Shape->perspective * x / z);
    dY = (48 / 2) + (Shape->perspective * y / z);


    Canvas->drawLine(sX,sY,dX,dY);
  };
};
