const int LeftMotor_F = 2;
const int LeftMotor_B = 3;
const int RightMotor_F = 0;
const int RightMotor_B = 1;

const int Dist_A = 8;
const int Dist_B = 9;

const int FORWARD = 0;
const int BACK = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NONE = 4;

int curDirection = 4;

void setup()
{
  pinMode(Dist_A,INPUT);
  pinMode(Dist_B,OUTPUT);
  
  pinMode(LeftMotor_F,OUTPUT);
  pinMode(RightMotor_F,OUTPUT);
  pinMode(LeftMotor_B,OUTPUT);
  pinMode(RightMotor_B,OUTPUT);
  pinMode(13,OUTPUT);
  
  randomSeed(analogRead(0));
}

void loop()
{
  // Reference:
  //
  // Go(FORWARD) - вперед
  // Go(BACK) - назад
  // Go(LEFT) - вліво
  // Go(RIGHT) - вправо
  //
  // getDistance(portA,portB) - отримати відстань до предмету в сантиметрах
  //             portA - порт A датчика
  //                   portB - порт B датчика
  
  goDistance(FORWARD,20.0);
  rotateDeg(135);
  goDistance(FORWARD,10.0);
  rotateDeg(-90);
  goDistance(FORWARD,10.0);
  rotateDeg(135);
  goDistance(FORWARD,20.0);
  
  delay(60000);
}

void Go(int Direction)
{
  if (curDirection == Direction) return;
  
  digitalWrite(LeftMotor_F,LOW);
  digitalWrite(LeftMotor_B,LOW);
  digitalWrite(RightMotor_F,LOW);
  digitalWrite(RightMotor_B,LOW);

  switch (Direction)
  {
  case FORWARD:
    digitalWrite(LeftMotor_F,HIGH);
    digitalWrite(RightMotor_F,HIGH);
    break;
  case BACK:
    digitalWrite(LeftMotor_B,HIGH);
    digitalWrite(RightMotor_B,HIGH);
    break;
  case LEFT:
    digitalWrite(LeftMotor_B,HIGH);
    digitalWrite(RightMotor_F,HIGH);
    break;
  case RIGHT:
    digitalWrite(LeftMotor_F,HIGH);
    digitalWrite(RightMotor_B,HIGH);
    break;
  }
  
  curDirection = Direction;
}


int getDistance(int portA,int portB)
{
  digitalWrite(portB,HIGH);
  delayMicroseconds(10);
  digitalWrite(portB,LOW);
  
  return pulseIn(portA,HIGH) / 58;
}


void rotateDeg(int deg)
{
  if (deg > 0)
  {
    Go(RIGHT);
  }
  else if (deg < 0)
  {
    Go(LEFT);
  }
  
  delay(abs(deg) * 46);
  Go(NONE);
}

void goDistance(int Direction,float Distance)
{
  if ((Direction != FORWARD) && (Direction != BACK)) return;
  
  Go(Direction);
  delay(Distance * 100);
  Go(NONE);
}

