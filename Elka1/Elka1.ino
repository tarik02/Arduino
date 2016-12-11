//#include <EEPROM.h>

//void(* reset) (void) = 0;

byte Programs[] =
{
  0x18,
  0x01,0x03,0x01,
  0x01,0x04,0x00,
  0x01,0x05,0x01,
  0x02,0xE8,0x03,
  0x01,0x03,0x00,
  0x01,0x04,0x01,
  0x01,0x05,0x00,
  0x02,0xE8,0x03,
  0x24,
  0x01,0x03,0x01,
  0x01,0x04,0x00,
  0x01,0x05,0x00,
  0x02,0xF4,0x01,
  0x01,0x03,0x00,
  0x01,0x04,0x01,
  0x01,0x05,0x00,
  0x02,0xF4,0x01,
  0x01,0x03,0x00,
  0x01,0x04,0x00,
  0x01,0x05,0x01,
  0x02,0xF4,0x01,
};
int ProgramPosition = 0;
int ProgramStart = 1;
byte ProgramSize = Programs[0];
byte ProgramIndex = 0;

unsigned short delayPos,delayLength;

void setup()
{
  for (int i = 1; i <= 13; i++)
  {
     pinMode(i,OUTPUT);
  };
  
  pinMode(7,INPUT);
  /*
  if (digitalRead(7) == HIGH)
  {
    Serial.begin(9600);
    
    while (!Serial);
    
    Serial.println("wait for commands");
    
    while (true)
    {
      int a = Serial.read();
      Serial.println(a,DEC);
      delay(1000);
      switch (Serial.read())
      {
        case 0:
        for (int i = 0; i < 512; i++)
        {
          Serial.println(i);
          EEPROM.write(i,0);
        };
        Serial.println("clearing done!");
        break;
        case 1:
        int startWriteIn = 1;
        
        if (EEPROM.read(0) == 0)
        {
        }
        else
        {
          while (EEPROM.read(startWriteIn) != 0)
          {
            startWriteIn += EEPROM.read(startWriteIn) + 1;
          };
        };
        
        byte size = Serial.read();
        
        for (int i = startWriteIn; i < startWriteIn + size; i++)
        {
          EEPROM.write(i,Serial.read());
        };
        
        EEPROM.write(0,EEPROM.read(0) + 1);
        
        Serial.println("reboot");
        
        reset();
        break;
      };
    };
  };
  */
}

void loop()
{
  if (delayLength == 0)
  {
    switch (Programs[ProgramStart + ProgramPosition++])
    {
      case 0x01:
      if (Programs[ProgramStart + ProgramPosition + 1] == 1)
      {
        digitalWrite(Programs[ProgramStart + ProgramPosition] + 1,HIGH);
      }
      else if (Programs[ProgramStart + ProgramPosition + 1] == 0)
      {
        digitalWrite(Programs[ProgramStart + ProgramPosition] + 1,LOW);
      };
      
      ProgramPosition += 2;
      break;
      case 0x02:
      delayPos = 0;
      delayLength = *(unsigned short *)(&Programs[ProgramStart + ProgramPosition]);
      ProgramPosition += 2;
      break;
    };
  }
  else
  {
    if (delayPos >= delayLength)
    {
      delayLength = 0;
    }
    else
    {
      delayPos++;
    };
  };
  
  if (ProgramPosition >= ProgramSize)
  {
    ProgramPosition = 0;
  };
  
  if (digitalRead(7) == HIGH)
  {
    while (digitalRead(7) == HIGH);
    
    ProgramPosition = 0;
    ProgramIndex++;
    ProgramStart = ProgramStart + ProgramSize + 1;
    ProgramSize = Programs[ProgramStart - 1];
    
    if (ProgramIndex == 2)
    {
      ProgramIndex = 0;
      ProgramStart = 1;
      ProgramSize = Programs[0];
    };
  };
  
  delay(1);
}
