#ifndef LCDH
#define LCDH
#include <Arduino.h>

#define swap(a, b) { int8_t t = a; a = b; b = t; }

class LCD
{
  private:
  const byte FRST,FCE,FDC,FDIN,FCLK;
  
  void WriteCmd(byte cmd);
  
  
  int8_t data[504];
  public:
  LCD(byte RST,byte CE,byte DC,byte DIN,byte CLK);
  
  void XY(int x,int y);
  void WriteString(char *characters);
  void WriteCharacter(char character);
  void WriteData(byte dat);
  
  void setPixel(int8_t X,int8_t Y,bool color);
  void drawLine(int8_t X1,int8_t Y1,int8_t X2,int8_t Y2,bool color = true);
  void drawVLine(int8_t X,int8_t Y,int8_t Height,bool color = true);
  void drawHLine(int8_t X,int8_t Y,int8_t Width,bool color = true);
  void drawRect(int8_t X1,int8_t Y1,int8_t X2,int8_t Y2,bool color = true);
  void drawFillRect(int8_t X1,int8_t Y1,int8_t X2,int8_t Y2,bool color = true);
  void drawBitmap(int8_t X,int8_t Y,int8_t Width,int8_t Height,const uint8_t *Bitmap);
  void drawBitmapPGM(int8_t X,int8_t Y,int8_t Width,int8_t Height,const uint8_t *Bitmap);
  void drawChar(int8_t X,int8_t Y,unsigned char Char,bool color = true);
  void drawCharSize(int8_t X,int8_t Y,unsigned char Char,int8_t size,bool color = true);
  void drawText(int8_t X,int8_t Y,char *text,bool color = true);
  void drawTextSize(int8_t X,int8_t Y,char *text,int8_t size,bool color = true);
  void clear();
  void display();
  void displayPart(int Part,int count);
};


#endif

