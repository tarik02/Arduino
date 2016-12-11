#include "font.h"
#include "LCD.h"

LCD::LCD(byte RST,byte CE,byte DC,byte DIN,byte CLK) : FRST(RST),FCE(CE),FDC(DC),FDIN(DIN),FCLK(CLK)
{
  pinMode(RST,OUTPUT);
  pinMode(CE,OUTPUT);
  pinMode(DC,OUTPUT);
  pinMode(DIN,OUTPUT);
  pinMode(CLK,OUTPUT);
  
  digitalWrite(RST,LOW);
  digitalWrite(RST,HIGH);
  
  WriteCmd(0x21);
  WriteCmd(0xB7);
  //WriteCmd(0xB5); // B5
  WriteCmd(0x04);
  WriteCmd(0x14);
  WriteCmd(0x20);
  WriteCmd(0x0C);
  
  for(int i = 0; i < 504; i++)
  {
    data[i] = 0x00;
    WriteData(0x00);
  };
};
void LCD::WriteString(char *characters)
{
  while(*characters) WriteCharacter(*characters++);
}

void LCD::WriteCharacter(char character)
{
  /*
  for (int i = 0; i < 5; i++)
    WriteData(ASCII[character - 0x20][i]);
  WriteData(0x00);
  */
}

void LCD::WriteData(byte dat)
{
  digitalWrite(FDC,HIGH);
  digitalWrite(FCE,LOW);
  shiftOut(FDIN,FCLK,MSBFIRST,dat);
  digitalWrite(FCE,HIGH);
}

void LCD::XY(int x, int y)
{
  WriteCmd(0x80 | x);
  WriteCmd(0x40 | y);
}

void LCD::WriteCmd(byte cmd)
{
  digitalWrite(FDC,LOW);
  digitalWrite(FCE,LOW);
  shiftOut(FDIN,FCLK,MSBFIRST,cmd);
  digitalWrite(FCE,HIGH);
}

void LCD::setPixel(int8_t X,int8_t Y,bool color)
{
  if ((X < 0) || (X >= 84) || (Y < 0) || (Y >= 48))
    return;
  
  if (color)
    data[X + (Y / 8) * 84] |= _BV(Y % 8);
  else
    data[X + (Y / 8) * 84] &= ~_BV(Y % 8);
};
void LCD::drawLine(int8_t X1,int8_t Y1,int8_t X2,int8_t Y2,bool color)
{
  bool steep = abs(Y2 - Y1) > abs(X2 - X1);
  
  if (steep)
  {
    swap(X1,Y1);
    swap(X2,Y2);
  };

  if (X1 > X2)
  {
    swap(X1,X2);
    swap(Y1,Y2);
  };

  int8_t dX,dY;
  dX = X2 - X1;
  dY = abs(Y2 - Y1);

  int8_t err = dX / 2;
  int8_t yStep;

  if (Y1 < Y2)
  {
    yStep = 1;
  }
  else
  {
    yStep = -1;
  };

  for (; X1 <= X2; X1++)
  {
    if (steep)
    {
      setPixel(Y1,X1,color);
    }
    else
    {
      setPixel(X1,Y1,color);
    };
    
    err -= dY;
    if (err < 0)
    {
      Y1 += yStep;
      err += dX;
    }
  }
};
void LCD::drawVLine(int8_t X,int8_t Y,int8_t Height,bool color)
{
  for (int i = 0; i <= Height; i++)
    setPixel(X,Y + i,color);
};
void LCD::drawHLine(int8_t X,int8_t Y,int8_t Width,bool color)
{
  for (int i = 0; i <= Width; i++)
    setPixel(X + i,Y,color);
};
void LCD::drawRect(int8_t X1,int8_t Y1,int8_t X2,int8_t Y2,bool color)
{
  if (X1 > X2)
    swap(X1,X2);
  if (Y1 > Y2)
    swap(Y1,Y2);
  
  int i;
  
  for (i = X1; i <= X2; i++)
  {
    setPixel(i,Y1,color);
    setPixel(i,Y2,color);
  };
  for (i = Y1; i <= Y2; i++)
  {
    setPixel(X1,i,color);
    setPixel(X2,i,color);
  };
};
void LCD::drawFillRect(int8_t X1,int8_t Y1,int8_t X2,int8_t Y2,bool color)
{
  if (X1 > X2)
    swap(X1,X2);
  if (Y1 > Y2)
    swap(Y1,Y2);
  
  int i,j;
  
  for (i = X1; i <= X2; i++)
    for (j = Y1; j <= Y2; j++)
      setPixel(i,j,color);
};
void LCD::drawBitmap(int8_t X,int8_t Y,int8_t Width,int8_t Height,const uint8_t *Bitmap)
{
  int8_t i,j,byteWidth = (Width + 7) / 8;
  
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      setPixel(X + i,Y + j,Bitmap[j * byteWidth + i / 8] & (128 >> (i & 7)));
    };
  };
};
void LCD::drawBitmapPGM(int8_t X,int8_t Y,int8_t Width,int8_t Height,const uint8_t *Bitmap)
{
  int8_t i,j,byteWidth = (Width + 7) / 8;
  
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      setPixel(X + i,Y + j,pgm_read_byte(Bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)));
    };
  };
};
void LCD::drawChar(int8_t X,int8_t Y,unsigned char Char,bool color)
{
  for (int8_t i = 0; i < 6; i++)
  {
    int8_t line;
    if (i == 5) 
      line = 0x00;
    else 
      line = pgm_read_byte(ASCII + ((Char - 0x20) * 5) + i);
    
    for (int8_t j = 0; j < 7; j++)
    {
      if (line & 0x1)
      {
        setPixel(X + i,Y + j,color);
      }
      else
      {
        setPixel(X + i,Y + j,!color);
      }
      line >>= 1;
    };
  };
};
void LCD::drawCharSize(int8_t X,int8_t Y,unsigned char Char,int8_t size,bool color)
{
  for (int8_t i = 0; i < 6; i++)
  {
    int8_t line;
    if (i == 5) 
      line = 0x00;
    else 
      line = pgm_read_byte(ASCII + ((Char - 0x20) * 5) + i);
    
    for (int8_t j = 0; j < 7; j++)
    {
      if (line & 0x1)
      {
        drawFillRect(X + (i * size),Y + (j * size),X + (i * size) + size,Y + (j * size) + size - 1,color);
      }
      else
      {
        drawFillRect(X + (i * size),Y + (j * size),X + (i * size) + size,Y + (j * size) + size - 1,!color);
      }
      line >>= 1;
    };
  };
};
void LCD::drawText(int8_t X,int8_t Y,char *text,bool color)
{
  int fX = X;
  
  while (*text)
  {
    drawChar(fX,Y,*text++,color);
    
    fX += 6;
  };
};
void LCD::drawTextSize(int8_t X,int8_t Y,char *text,int8_t size,bool color)
{
  int fX = X;
  
  while (*text)
  {
    drawCharSize(fX,Y,*text++,size,color);
    
    fX += size * 6;
  };
};
void LCD::clear()
{
  for (int i = 0; i < 504; i++)
    data[i] = 0x00;
};
void LCD::display()
{
  int i;
  XY(0,0);
  
  for (i = 0; i < 504; i++)
  {
    WriteData(data[i]);
  };
};
void LCD::displayPart(int Part,int count)
{
  XY(Part % 84,Part / 84);
  
  for (int i = Part; i < Part + count; i++)
  {
    WriteData(data[i]);
  }
};

