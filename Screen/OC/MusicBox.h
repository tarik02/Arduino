
static const unsigned char MusicBoxIcon[] PROGMEM =
{
  B00001000,B00000100,B00000000,
  B00001000,B00000100,B00000000,
  B00001100,B00000110,B00000000,
  B00001110,B00000111,B00000000,
  B00001001,B00000100,B10000000,
  B00001001,B00000100,B10000000,
  B00001001,B00000100,B10000000,
  B00001001,B00000100,B10000000,
  B00001000,B00000100,B00000000,
  B01111000,B00111100,B00000000,
  B11111000,B01111100,B00000000,
  B11110000,B01111000,B00000000,
};

int TMusicBox_melody_length = 8;

int TMusicBox_melody[][8] = {
                             {NOTE_C4,NOTE_G3,NOTE_G3,NOTE_A3,NOTE_G3,0,NOTE_B3,NOTE_C4},
                             {NOTE_G3,NOTE_C4,NOTE_C4,NOTE_C4,NOTE_C4,0,NOTE_C3,NOTE_G3},
                             {NOTE_CS4,NOTE_CS4,NOTE_D4,NOTE_D4,NOTE_DS1,0,NOTE_DS1,NOTE_A5},
                             {NOTE_GS5,NOTE_GS4,NOTE_A4,NOTE_F4,NOTE_FS1,0,NOTE_F6,NOTE_F1}
                            };

int TMusicBox_durations[] = {4,8,8,4,4,4,4,4};

class TMusicBox : public TProgram
{
  private:
  TSounds *mSounds;
  TSound *mSound;
  public:
  TMusicBox();
  
  void Start();
  void ReadButtons(byte &Buttons);
  void Paint(LCD *Canvas);
};

TMusicBox::TMusicBox() : TProgram(true)
{
  icon = (unsigned char *)MusicBoxIcon;
  
  mSounds = new TSounds(13);
};
void TMusicBox::Start()
{
  mSound = Sound(TMusicBox_melody[random(0,4)],TMusicBox_durations,TMusicBox_melody_length);
  
  mSounds->Play(mSound,true);
};
void TMusicBox::ReadButtons(byte &Buttons)
{
    if ((Buttons | _BV(1)) == Buttons)
    {
      Buttons &= ~_BV(1);
    }
};
void TMusicBox::Paint(LCD *Canvas)
{
  
};

