const int LeftMotor_F = 5;
const int LeftMotor_B = 4;
const int RightMotor_F = 7;
const int RightMotor_B = 6;

const int Dist_A = 8;
const int Dist_B = 9;

const int FORWARD = 0;
const int BACK = 1;
const int NONE = 2;

int curDirection = 4;

int defRot;

void setup()
{
  pinMode(Dist_A,INPUT);
  pinMode(Dist_B,OUTPUT);
  
  pinMode(LeftMotor_F,OUTPUT);
  pinMode(RightMotor_F,OUTPUT);
  pinMode(LeftMotor_B,OUTPUT);
  pinMode(RightMotor_B,OUTPUT);
  
  randomSeed(analogRead(0));
  
  defRot = (random(100) < 50) ? -90 : 90;
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
  
  unsigned int Distance = getDistance(Dist_A,Dist_B);
  
  if (Distance < 30)
  {
    goDistance(BACK,10);
    rotateDeg(defRot);
  }
  else
  {
    goDistance(FORWARD,3);
  };
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
    digitalWrite(LeftMotor_F,HIGH);
    digitalWrite(RightMotor_B,HIGH);
    digitalWrite(LeftMotor_B,LOW);
    digitalWrite(RightMotor_F,LOW);
  }
  else if (deg < 0)
  {
    digitalWrite(LeftMotor_B,HIGH);
    digitalWrite(RightMotor_F,HIGH);
    digitalWrite(LeftMotor_F,LOW);
    digitalWrite(RightMotor_B,LOW);
  };
  
  delay(abs(deg) * 46);
  
  digitalWrite(LeftMotor_B,LOW);
  digitalWrite(RightMotor_F,LOW);
  digitalWrite(LeftMotor_F,LOW);
  digitalWrite(RightMotor_B,LOW);
}

void goDistance(int Direction,float Distance)
{
  if (Direction == FORWARD)
  {
    digitalWrite(LeftMotor_F,HIGH);
    digitalWrite(RightMotor_F,HIGH);
    digitalWrite(LeftMotor_B,LOW);
    digitalWrite(RightMotor_B,LOW);
  }
  else if (Direction == BACK)
  {
    digitalWrite(LeftMotor_B,HIGH);
    digitalWrite(RightMotor_B,HIGH);
    digitalWrite(LeftMotor_F,LOW);
    digitalWrite(RightMotor_F,LOW);
  }
  else
  {
    digitalWrite(LeftMotor_B,LOW);
    digitalWrite(RightMotor_F,LOW);
    digitalWrite(LeftMotor_F,LOW);
    digitalWrite(RightMotor_B,LOW);
    return;
  };
  
  delay(Distance * 100);
  digitalWrite(LeftMotor_B,LOW);
  digitalWrite(RightMotor_F,LOW);
  digitalWrite(LeftMotor_F,LOW);
  digitalWrite(RightMotor_B,LOW);
}

