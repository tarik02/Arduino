struct Vertex
{
  float x,y,z;
  Vertex(float x,float y,float z) : x(x),y(y),z(z) {  };
};

struct Edge
{
  uint8_t src,dest;
  Edge(uint8_t src,uint8_t dest) : src(src),dest(dest) {  };
};

struct Object3D
{
  const int EdgesCount;
  Edge *Edges;
  
  const int VerticesCount;
  Vertex *Vertices;
  
  float x,y,z;
  
  Object3D(int EdgesCount,int VerticesCount) : EdgesCount(EdgesCount),VerticesCount(VerticesCount) { Edges = (Edge *)malloc(EdgesCount * sizeof(Edge)); Vertices = (Vertex *)malloc(VerticesCount * sizeof(Vertex)); };
  ~Object3D() { free(Edges); };
};
/*
typedef float Matrix[4][4];
typedef float Column[4];
*/

class Column
{
  float data[4];
};

class Matrix
{
  fl data[4][4];
};

Matrix MMMult(Matrix lhs,Matrix rhs)
{
  int i,j,k;
  Matrix Result;
  float s;
  
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
    {
      s = 0;
      for (k = 0; k < 4; k++)
        s = s + lhs.data[i][k] * rhs.data[k][j];
      Result.data[i][j] = s;
    };
  
  return Result;
};

Column MCMult(Matrix lhs,Column rhs)
{
  int i,k;
  float s;
  Column Result;
  
  for (i = 0; i < 4; i++)
  {
    s = 0;
    
    for (k = 0; k < 4; k++)
      s = s + lhs[i][k] * rhs[k];
    Result[i] = s;
  };
  
  return Result;
};

Matrix RotateMatrix(float xa,float ya,float za)
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
  
  return MMMult(MMMult(xr,yr),zr);
};


void RotateShape(Object3D &Shape,float xa,float ya,float za)
{
  Matrix rm;
  int i;
  Column c;
  
  rm = RotateMatrix(xa,ya,za);
  c[3] = 1;
  
  for (i = 0; i < Shape.VerticesCount; i++)
  {
    c[0] = Shape.Vertices[i].x;
    c[1] = Shape.Vertices[i].y;
    c[2] = Shape.Vertices[i].z;
    
    c = MCMult(rm,c);
    
    Shape.Vertices[i].x = c[0];
    Shape.Vertices[i].y = c[1];
    Shape.Vertices[i].z = c[2];
  };
};

void ShowShape(LCD *Screen,Object3D Shape)
{
  int i,Xs1,Ys1,Xs2,Ys2;
  float x,y,z;
  const uint8_t N = 15;
  
  for (i = 0; i < Shape.EdgesCount; i++)
  {
    x = Shape.Vertices[Shape.Edges[i].src].x + Shape.x;
    y = Shape.Vertices[Shape.Edges[i].src].y + Shape.y;
    z = Shape.Vertices[Shape.Edges[i].src].z + Shape.z;
    if (abs(z) < 0.01)
      z = 0.01;
    
    Xs1 = round((84 / 2) + N * x / z);
    Ys1 = round((48 / 2) + N * y / z);
    
    x = Shape.Vertices[Shape.Edges[i].dest].x + Shape.x;
    y = Shape.Vertices[Shape.Edges[i].dest].y + Shape.y;
    z = Shape.Vertices[Shape.Edges[i].dest].z + Shape.z;
    if (abs(z) < 0.01)
      z = 0.01;
    
    Xs2 = round((84 / 2) + N * x / z);
    Ys2 = round((48 / 2) + N * y / z);
    
    Screen->drawLine(Xs1,Ys1,Xs2,Ys2);
  };
};




















