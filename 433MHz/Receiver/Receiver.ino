#include <VirtualWire.h>

#define LEFT_MOTOR_1 6
#define LEFT_MOTOR_2 7

#define RIGHT_MOTOR_1 4
#define RIGHT_MOTOR_2 5

#define DIST_1 12
#define DIST_2 13

#define SERVO 9

#define FORWARD 1
#define BACK 2
#define LEFT 3
#define RIGHT 4

class TMotor
{
  private:
  const unsigned char lm1,lm2;
  const unsigned char rm1,rm2;
  public:
  TMotor(unsigned char lm1,unsigned char lm2,unsigned char rm1,unsigned char rm2) : lm1(lm1),lm2(lm2),rm1(rm1),rm2(rm2) {};
  
  void attach()
  {
    pinMode(lm1,OUTPUT);
    pinMode(lm2,OUTPUT);
    pinMode(rm1,OUTPUT);
    pinMode(rm2,OUTPUT);
  };
  
  void go(unsigned char direction,unsigned char distance = 0)
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
    
    if (distance != 0)
    {
      delay(distance * 100);
      stop();
    }
  };
  void rotate(short angle)
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
  void rotateSide(unsigned char side)
  {
    switch (side)
    {
      case LEFT:
        digitalWrite(lm1,LOW);
        digitalWrite(lm2,HIGH);
        digitalWrite(rm1,HIGH);
        digitalWrite(rm2,LOW);
        break;
      case RIGHT:
        digitalWrite(lm1,HIGH);
        digitalWrite(lm2,LOW);
        digitalWrite(rm1,LOW);
        digitalWrite(rm2,HIGH);
        break;
    };
  };
  void stop()
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
  
  void attach() { pinMode(Pin,OUTPUT); };
  
  void spin(unsigned char Angle,unsigned char Speed = 15)
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
  
  void attach() { pinMode(Pin1,INPUT); pinMode(Pin2,OUTPUT); };
  
  unsigned short read()
  {
    digitalWrite(Pin2,HIGH);
    delayMicroseconds(10);
    digitalWrite(Pin2,LOW);
    
    return pulseIn(Pin1,HIGH) / 58;
  };
};


void getMessage(void (*callback)(char,char *))
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf,&buflen))
  {
    int i;
    
    if (buf[0] != 'z')
      return; 
    
    char command = buf[2];
    
    i = 4; 
    char param[VW_MAX_MESSAGE_LEN - 5];
    
    while (buf[i] != ' ')
    {
      param[i - 4] = buf[i];
      i++;
    };
    param[i - 4] = 0;
    
    callback(command,param);
  };
};

TMotor Motor = TMotor(LEFT_MOTOR_1,LEFT_MOTOR_2,RIGHT_MOTOR_1,RIGHT_MOTOR_2);
TServo Servo = TServo(SERVO);
TDistanceSensor DistanceSensor = TDistanceSensor(DIST_1,DIST_2);


bool Mode = false;
uint64_t lastActive = 0;


unsigned short LastMax = 0,Val = 0;
unsigned char LastMaxRot = 0;




void messageCallback(char command,char *params)
{
  Mode = true;
  lastActive = millis();
  
  switch (command)
  {
    case 'g':
      switch (params[0])
      {
        case '1':
          Motor.go(FORWARD);
          break;
        case '2':
          Motor.go(BACK);
          break;
      };
      break;
    case 'r':
      switch (params[0])
      {
        case '1':
          Motor.rotate(-15);
          break;
        case '2':
          Motor.rotate(15);
          break;
      };
      break;
    case 'h':
      switch (params[0])
      {
        case '1':
          Servo.spin(max(Servo.Pos + 20,0),15);
          break;
        case '2':
          Servo.spin(min(Servo.Pos - 20,180),15);
          break;
      };
      break;
    case 'o':
      switch (params[0])
      {
        case 's':
          Motor.stop();
          break;
      };
    break;
  };
};

void setup()
{
  Serial.begin(9600);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_rx_start();
  
  Motor.attach();
  Servo.attach();
  DistanceSensor.attach();
  
  Servo.spin(90,10);
};

void loop()
{
  getMessage(messageCallback);
  
  if (Mode)
  {
    if ((millis() - lastActive) >= 60000)
    {
      lastActive = millis();
      Mode = false;
    };
  }
  else
  {
    if (DistanceSensor.read() <= 30)
    {
      Val = 0;
      LastMax = 0;
      LastMaxRot = 0;
      
      Motor.stop();
      Servo.spin(45,20);
      for (int i = 0; i < 30; i++)
      {
        Servo.spin(45 + (i * 3),10);
        Val = DistanceSensor.read();
        if (Val >= LastMax)
        {
          LastMax = Val;
          LastMaxRot = i;
        }
      }
      
      Servo.spin(90,20);
      
      if (LastMax >= 40)
        Motor.rotate(-(-45 + (LastMaxRot * 3)));
      else
        Motor.go(BACK,5);
    }
    else
    {
      Motor.go(FORWARD);
    }
  };
};







