#ifndef _LIB3DH_
#define _LIB3DH_
#include <Arduino.h>
#include "LCD.h"

struct Vertex
{
  float x,y,z;
  Vertex() {  };
  Vertex(float fX,float fY,float fZ) : x(fX), y(fY), z(fZ) {  };
};

struct Edge
{
  uint8_t src,dst;
  Edge() {  };
  Edge(uint8_t fSrc,uint8_t fDst) : src(fSrc), dst(fDst) {  };
};

class TObject3D
{
  private:
  public:
  const int verticesCount;
  const int edgesCount;
  
  Vertex *vertices;
  Edge *edges;
  
  int perspective;
  
  float x,y,z;
  
  TObject3D(uint8_t fvc,uint8_t fec,int persp) : verticesCount(fvc), edgesCount(fec), perspective(persp), x(0), y(0), z(0)
  {
    vertices = new Vertex[verticesCount];
    edges = new Edge[edgesCount];
  };
};

typedef float Matrix[4][4];
typedef float Column[4];

void MMMult(Matrix lhs,Matrix rhs,Matrix &r);
void MCMult(Matrix lhs,Column rhs,Column &r);
void RotateMatrix(float xa,float ya,float za,Matrix &r);
void RotateShape(TObject3D *Shape,float xa,float ya,float za);
void ShowShape(TObject3D *Shape,LCD *Screen);

#endif
