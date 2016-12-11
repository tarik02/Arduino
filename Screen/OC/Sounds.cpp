#include "Timer.h"
#include "Sounds.h"


TSound *Sound(int *melody,int *durations,int length)
{
  TSound *Result = new TSound;
  Result->melody = melody;
  Result->durations = durations;
  Result->length = length;
  
  return Result;
}


void TSounds_onMusicTimer(void *Data)
{
  if (((TSounds *)Data)->Active)
  {
    long noteDuration = 1300 / ((TSounds *)Data)->cSound->durations[((TSounds *)Data)->Position];
    
    tone(((TSounds *)Data)->Out,((TSounds *)Data)->cSound->melody[((TSounds *)Data)->Position],noteDuration);
    
    int pauseBetweenNotes = noteDuration * 1.05;
    
    if ((((TSounds *)Data)->Position + 1 >= ((TSounds *)Data)->cSound->length))
    {
      if (!((TSounds *)Data)->PlayLoop)
      {
        ((TSounds *)Data)->Active = false;
        //((TSounds *)Data)->Stop();
        //delete ((TSounds *)Data)->cSound;
        //((TSounds *)Data)->cSound = 0;
        return;
      }
    }
    
    ((TSounds *)Data)->Position = (((TSounds *)Data)->Position + 1) % ((TSounds *)Data)->cSound->length;
    
    ((TSounds *)Data)->Timer->Interval = pauseBetweenNotes;
    //addTimer(/*noteDuration*/pauseBetweenNotes,true,TSounds_onMusicTimer,Data);
  }
  else
  {
    //digitalWrite(((TSounds *)Data)->Out,LOW);
    //noTone(((TSounds *)Data)->Out);
  };
};

TSounds::TSounds(int out) : Out(out)
{
  //pinMode(Out,OUTPUT);
  cSound = 0;
  Active = false;
  //Timer = addTimer(0,false,TSounds_onMusicTimer,this);
};
TSounds::~TSounds()
{
  if (cSound != 0)
  {
    delete cSound;
    cSound = 0;
  }
};

void TSounds::Play(TSound *Sound,bool Loop)
{
  if (cSound != 0)
  {
    delete cSound;
    cSound = 0;
  }
  
  cSound = new TSound();
  memcpy(cSound,Sound,sizeof(TSound));
  
  Active = true;
  PlayLoop = Loop;
  Position = 0;
  //Timer = addTimer(0,true,TSounds_onMusicTimer,this);
  /*
  for (int thisNote = 0; thisNote < Sound->length; thisNote++)
  {
    int noteDuration = 1000 / Sound->durations[thisNote];
    tone(Out,Sound->melody[thisNote],noteDuration);
    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(Out);
  }
  */
};
void TSounds::Stop()
{
  Active = false;
};

