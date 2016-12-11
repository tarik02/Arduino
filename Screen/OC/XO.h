
static const unsigned char XOIcon[] PROGMEM =
{
  B10100100,B01000000,B00000000,
  B01001010,B10100000,B00000000,
  B10100100,B01000000,B00000000,
  B00010000,B00000000,B00000000,
  B00001010,B00000000,B00000000,
  B00000100,B00000000,B00000000,
  B00001010,B00000000,B00000000,
  B00000001,B00000000,B00000000,
  B00000000,B10100000,B00000000,
  B00000000,B01000000,B00000000,
  B00000000,B10100000,B00000000,
  B00000000,B00000000,B00000000,
};

static const unsigned char XO1[] PROGMEM =
{
  B10000000,B00100000,
  B01000000,B01000000,
  B00100000,B10000000,
  B00010001,B00000000,
  B00001010,B00000000,
  B00000100,B00000000,
  B00001010,B00000000,
  B00010001,B00000000,
  B00100000,B10000000,
  B01000000,B01000000,
  B10000000,B00100000,
  B00000000,B00000000,
};
static const unsigned char XO2[] PROGMEM =
{
  B00000110,B00000000,
  B00001001,B00000000,
  B00010000,B10000000,
  B00100000,B01000000,
  B01000000,B00100000,
  B10000000,B00010000,
  B10000000,B00010000,
  B01000000,B00100000,
  B00100000,B01000000,
  B00010000,B10000000,
  B00001001,B00000000,
  B00000110,B00000000,
};

class TXO : public TProgram
{
  friend void TXOonLoadingTimer(void *Data);
  private:
  TTimer *LoadingTimer;
  
  byte field[9];
  int8_t cursorPos;
  
  bool hid;
  
  bool isWin(int pl);
  
  bool Loading;
  public:
  TXO();
  
  void Start();
  void ReadButtons(byte &Buttons);
  void Paint(LCD *Canvas);
};

void TXOonLoadingTimer(void *Data)
{
  ((TXO *)Data)->Loading = false;
  for (int i = 0; i < 9; i++)
    ((TXO *)Data)->field[i] = 0;
}

TXO::TXO() : TProgram(true)
{
  icon = (unsigned char *)XOIcon;
};
bool TXO::isWin(int pl)
{
  return ((field[0] == pl) && (field[1] == pl) && (field[2] == pl)) ||
         ((field[3] == pl) && (field[4] == pl) && (field[5] == pl)) ||
         ((field[6] == pl) && (field[7] == pl) && (field[8] == pl)) ||
         ((field[0] == pl) && (field[3] == pl) && (field[6] == pl)) ||
         ((field[1] == pl) && (field[4] == pl) && (field[7] == pl)) ||
         ((field[2] == pl) && (field[5] == pl) && (field[8] == pl)) ||
         ((field[0] == pl) && (field[4] == pl) && (field[8] == pl)) ||
         ((field[2] == pl) && (field[4] == pl) && (field[6] == pl));
};
void TXO::Start()
{
  LoadingTimer = addTimer(2500,true,TXOonLoadingTimer,this);
  
  for (int i = 0; i < 9; i++)
    field[i] = 0;
  
  cursorPos = 4;
  
  hid = true;
  
  Loading = true;
};
void TXO::ReadButtons(byte &Buttons)
{
    if ((Buttons | _BV(1)) == Buttons)
    {
      Buttons &= ~_BV(1);
      cursorPos -= 3;
    }
    if ((Buttons | _BV(2)) == Buttons)
    {
      Buttons &= ~_BV(2);
      cursorPos -= 1;
    }
    if ((Buttons | _BV(3)) == Buttons)
    {
      Buttons &= ~_BV(3);
      
      if (field[cursorPos] == 0)
        field[cursorPos] = hid ? 1 : 2;
      
      if (isWin(hid ? 1 : 2))
      {
        LoadingTimer = addTimer(1500,true,TXOonLoadingTimer,this);
      }
      
      if (hid)
        hid = false;
      else
        hid = true;
    }
    if ((Buttons | _BV(4)) == Buttons)
    {
      Buttons &= ~_BV(4);
      cursorPos += 1;
    }
    if ((Buttons | _BV(5)) == Buttons)
    {
      Buttons &= ~_BV(5);
      cursorPos += 3;
    }
    
    if (cursorPos < 0)
      cursorPos = 9 - cursorPos;
    if (cursorPos >= 9)
      cursorPos = cursorPos - 9;
};
void TXO::Paint(LCD *Canvas)
{
  Canvas->drawVLine(18 + 16,0,48);
  Canvas->drawVLine(18 + 32,0,48);
  
  Canvas->drawHLine(18,16,48);
  Canvas->drawHLine(18,32,48);
  
  if (Loading)
  {
    Canvas->drawBitmapPGM(18 + 2,2,12,12,XO1);
    Canvas->drawBitmapPGM(18 + 18,18,12,12,XO1);
    Canvas->drawBitmapPGM(18 + 34,34,12,12,XO1);
    
    Canvas->drawBitmapPGM(18 + 18,2,12,12,XO2);
    Canvas->drawBitmapPGM(18 + 34,2,12,12,XO2);
    
    Canvas->drawLine(18 + 2,2,18 + 46,46);
  }
  else
  {
    for (int i = 0; i < 9; i++)
    {
      switch (field[i])
      {
        case 0:
        break;
        case 1:
        Canvas->drawBitmapPGM(18 + (16 * (i % 3)) + 2,(16 * int(i / 3)) + 2,12,12,XO1);
        break;
        case 2:
        Canvas->drawBitmapPGM(18 + (16 * (i % 3)) + 2,(16 * int(i / 3)) + 2,12,12,XO2);
        break;
      }
    }
    
    
    Canvas->drawFillRect(18 + (16 * (cursorPos % 3) + 5),(16 * int(cursorPos / 3) + 5),18 + (16 * (cursorPos % 3) + 9),(16 * int(cursorPos / 3) + 9));
    
    

  };
};

