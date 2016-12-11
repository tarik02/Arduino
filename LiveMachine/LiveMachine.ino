#define LEFT_MOTOR_1 6
#define LEFT_MOTOR_2 7

#define RIGHT_MOTOR_1 4
#define RIGHT_MOTOR_2 5

#define DIST_1 10
#define DIST_2 11

#define SERVO 9

#define FORWARD 1
#define BACK 2

class TMotor
{
  private:
  const unsigned char lm1,lm2;
  const unsigned char rm1,rm2;
  public:
  TMotor(unsigned char lm1,unsigned char lm2,unsigned char rm1,unsigned char rm2) : lm1(lm1),lm2(lm2),rm1(rm1),rm2(rm2) {};
  
  void Attach()
  {
    pinMode(lm1,OUTPUT);
    pinMode(lm2,OUTPUT);
    pinMode(rm1,OUTPUT);
    pinMode(rm2,OUTPUT);
  };
  
  void Go(unsigned char direction,unsigned char distance = 0)
  {
    if (direction == FORWARD)
    {
      digitalWrite(lm1,HIGH);
      digitalWrite(lm2,LOW);
      digitalWrite(rm1,HIGH);
      digitalWrite(rm2,LOW);
    }
    else if (direction == BACK)
    {
      digitalWrite(lm1,LOW);
      digitalWrite(lm2,HIGH);
      digitalWrite(rm1,LOW);
      digitalWrite(rm2,HIGH);
    };
    
    delay(distance * 100);
  };
  void Rotate(unsigned short angle)
  {
    if (angle > 0)
    {
      digitalWrite(lm1,HIGH);
      digitalWrite(lm2,LOW);
      digitalWrite(rm1,LOW);
      digitalWrite(rm2,HIGH);
    }
    else
    {
      digitalWrite(lm1,LOW);
      digitalWrite(lm2,HIGH);
      digitalWrite(rm1,HIGH);
      digitalWrite(rm2,LOW);
    };
    
    delay(abs(angle) * 46);
    
    
    digitalWrite(lm1,LOW);
    digitalWrite(lm2,LOW);
    digitalWrite(rm1,LOW);
    digitalWrite(rm2,LOW);
  };
  void Stop()
  {
    digitalWrite(lm1,LOW);
    digitalWrite(lm2,LOW);
    digitalWrite(rm1,LOW);
    digitalWrite(rm2,LOW);
  };
};

class TServo
{
  private:
  const unsigned char Pin;
  public:
  TServo(const unsigned char Pin) : Pin(Pin) {  };
  
  unsigned char Pos;
  
  void Attach() { pinMode(Pin,OUTPUT); };
  
  void Spin(unsigned char Angle,unsigned char Speed = 15)
  {
    Speed = 25 - Speed;
    
    while (Pos != Angle)
    {
      Pos = Pos + ((Pos > Angle) ? -1 : 1);
      digitalWrite(Pin,HIGH);
      delayMicroseconds((Pos * 11) + 500);
      digitalWrite(Pin,LOW);
      delay(Speed);
    };
  };
};

class TDistanceSensor
{
  private:
  const unsigned char Pin1,Pin2;
  public:
  TDistanceSensor(unsigned char Pin1,unsigned char Pin2) : Pin1(Pin1),Pin2(Pin2) {  };
  
  void Attach() { pinMode(Pin1,INPUT); pinMode(Pin2,OUTPUT); };
  
  unsigned short Read()
  {
    digitalWrite(Pin2,HIGH);
    delayMicroseconds(10);
    digitalWrite(Pin2,LOW);
    
    return pulseIn(Pin1,HIGH) / 58;
  };
};

TMotor Motor = TMotor(LEFT_MOTOR_1,LEFT_MOTOR_2,RIGHT_MOTOR_1,RIGHT_MOTOR_2);
TServo Servo = TServo(SERVO);
TDistanceSensor DistanceSensor = TDistanceSensor(DIST_1,DIST_2);

void setup()
{
  Motor.Attach();
  Servo.Attach();
  DistanceSensor.Attach();
  
  Motor.Go(FORWARD);
}

bool HeadAngleDirection = false;
unsigned char HeadAngle = 45;
unsigned short Data[60];

unsigned int stopTime = 0;

void loop()
{
  Servo.Spin(HeadAngle * 3,24);
  Data[HeadAngle] = DistanceSensor.Read();
  
  if ((HeadAngle >= 20) && (HeadAngle <= 40))
  {
    if (Data[HeadAngle] <= 30)
    {
      stopTime = millis() + (10 * 100);
      Motor.Go(BACK);
    };
  };
  
  if (HeadAngleDirection)
    HeadAngle -= 1;
  else
    HeadAngle += 1;
  if ((HeadAngle == 0) || (HeadAngle == 60))
    HeadAngleDirection = !HeadAngleDirection;
  
  
  if (stopTime == 0)
  {
    //Motor.Go(FORWARD);
  }
  else if (stopTime >= millis())
  {
    unsigned short val = Data[0],idx = 0,i = 0;
    for (i = 0; i < 60; i++)
    {
      if (Data[i] > val)
      {
        idx = i;
        val = Data[i];
      };
    };
    
    if (val > 50)
    {
      stopTime = 0;
      Motor.Rotate(idx * 3);
      Motor.Go(FORWARD);
    }
    else
    {
      stopTime = millis() + (100 * 10);
      Motor.Go(BACK);
    }
  };
  
  
  //Motor.Go(FORWARD);
  // 4 - R F
  // 5 - R B
  // 6 - L F
  // 7 - L B
  //digitalWrite(7,HIGH);
}
