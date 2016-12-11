#include <VirtualWire.h>
#include <NewPing.h>
//#include <TimerOne.h>
//#include <Servo.h>

#include "Scheduler.h"
#include "AsyncServo.h"
#include "TwoMotorControl.h"
#include "DistanceSensor.h"


enum Direction { D_NONE, D_FORWARD, D_BACK, D_LEFT, D_RIGHT };
enum Rotation { R_NONE, R_LEFT, R_RIGHT };


const unsigned char receivePin = 8;
const unsigned char servoPin = 9;

const unsigned char leftMotorPin1 = 6;
const unsigned char leftMotorPin2 = 7;

const unsigned char rightMotorPin1 = 4;
const unsigned char rightMotorPin2 = 5;

const unsigned char sonarEchoPin = 2;
const unsigned char sonarTrigPin = 3;



void dispatchMessage(byte *data, unsigned char len);
void loop2();


Scheduler scheduler;
AsyncServo servo(servoPin, 90);
TwoMotorControl machine(leftMotorPin1, leftMotorPin2, rightMotorPin1, rightMotorPin2);
//DistanceSensor sonar(sonarEchoPin, sonarTrigPin);
NewPing sonar(sonarTrigPin, sonarEchoPin, 200);


unsigned long lastControl = 0;
unsigned long lastReceiveTry = 0;

Rotation rotation = R_NONE;
Direction direction = D_NONE;


volatile unsigned int distance = 0;
unsigned int checking = 0;

unsigned int checkingAngle = 0;
unsigned int checkingValue = 0;

unsigned long checkingReturnBackTime;


unsigned long lastRotate = 0;


void sonar_ping_callback()
{
  if (!sonar.check_timer())
  {
    return;
  }

  if (sonar.ping_result != 0)
  {
    distance = sonar.convert_cm(sonar.ping_result);
  }
}

void setup()
{
  Serial.begin(9600);

  vw_set_rx_pin(receivePin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_rx_start();
  
  servo.attach();
  machine.attach();
  //sonar.attach();

  sonar.ping_timer(sonar_ping_callback);

  scheduler.post(20, [](unsigned int diff)
    {
      /*if (millis() - lastControl <= 1000)
      {
        
      }
      else
      {
        if ((millis() - lastReceiveTry >= 100) && (millis() - lastReceiveTry <= 2000))
        {
          //digitalWrite(10, false);
          //vw_rx_stop();
          sonar.ping_timer(sonar_ping_callback);
        }
        else if (millis() - lastReceiveTry >= 2000)
        {
          lastReceiveTry = millis();

          vw_set_rx_pin(receivePin);
          vw_set_ptt_inverted(true);
          vw_setup(2000);
          vw_rx_start();
        }
      }*/

      sonar.ping_timer(sonar_ping_callback);
    }, true);

  /*scheduler.post(100, [](unsigned int diff)
    {
      Serial.println(distance);
    }, true);*/


  /*Timer1.initialize(1000);
  Timer1.pwm(9, 512);
  Timer1.attachInterrupt(tick_loop);*/
}


void tick_loop();
void logic_loop();

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN + 1];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf, &buflen))
  {
    buf[buflen] = 0x00;
    
    if ((buf[0] == 0xFD) && (buf[1] == 0xC9))
    {
      dispatchMessage(buf + 2, buflen - 2);
    }
  }

  tick_loop();
  logic_loop();
}

void tick_loop()
{
  servo.tick();
  machine.tick();
  scheduler.tick();
}


bool lastMode = false;

void logic_loop()
{
  if (millis() - lastControl < 1000)
  {
    if (lastMode != false)
    {
      Serial.println("Mode changed to control");
      lastMode = false;
    }
    
    switch (direction)
    {
      case D_FORWARD:
        machine.go(1);
        break;
      case D_BACK:
        machine.go(-1);
        break;
      case D_LEFT:
        machine.rotate(-1);
        break;
      case D_RIGHT:
        machine.rotate(1);
        break;
      case D_NONE:
        machine.stop();
        break;
    }

    auto servoAngle = servo.getAngle();
    
    switch (rotation)
    {
      case R_LEFT:
        if ((servoAngle != 180) && (millis() - lastRotate < 50))
        {
          lastRotate = millis();
          servo.spin(servoAngle + 1);
        }
        break;
      case R_RIGHT:
        if ((servoAngle != 0) && (millis() - lastRotate < 50))
        {
          lastRotate = millis();
          servo.spin(servoAngle - 1);
        }
        break;
    }
  }
  else
  {
    if (lastMode != true)
    {
      Serial.println("Mode changed to auto");
      lastMode = true;
    }
    
    /*switch (checking)
    {
      case 0:
        if (distance > 15)
        {
          machine.go(1);
        }
        else
        {
          machine.stop();
          servo.spin(45);
          checking = 1;
        }
        break;
      case 1:
        if (servo.getPos() <= 45)
        {
          checking = 2;

          checkingAngle = 45;
          checkingValue = distance;

          servo.spin(90 + 45);
        }
        break;
      case 2:
        if (servo.getPos() >= 90 + 45)
        {
          checking = 3;
        }
        else
        {
          if (checkingValue < distance)
          {
            checkingAngle = servo.getPos();
            checkingValue = distance;
          }
        }
        break;
      case 3:
        checking = 4;
        servo.spin(90);
        
        if (checkingValue <= 15)
        {
          checkingReturnBackTime = millis() + machine.go(-15);
        }
        else
        {
          checkingReturnBackTime = millis() + machine.rotate((90 - checkingAngle) > 0 ? -45 : 45);
        }
        break;
      case 4:
        if (checkingReturnBackTime <= millis())
        {
          checking = 0;
        }
        break;
    }*/


    Serial.println(distance);
    
    if (checkingReturnBackTime <= millis())
    {
      if (distance < 30)
      {
        auto time = machine.go(-15);
        checkingReturnBackTime = millis() + time;
        scheduler.post(time, [](unsigned int diff)
          {
            checkingReturnBackTime = millis() + machine.rotate(rand() % 2 == 0 ? 45 : -45);
          });
        
      }
      else
      {
        machine.go(15);
      }
    }
  }
}

void dispatchMessage(byte *data, unsigned char len)
{
  switch (data[0])
  {
    case 'i':
      lastControl = millis();
      direction = (Direction)data[1];
      rotation = (Rotation)data[2];
      break;
    case 's':
      lastControl = 0;
      break;
  }
}

















