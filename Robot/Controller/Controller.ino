#include <Key.h>
#include <Keypad.h>
#include <VirtualWire.h>

#define DEBUG

enum Direction { D_NONE, D_FORWARD, D_BACK, D_LEFT, D_RIGHT };
enum Rotation { R_NONE, R_LEFT, R_RIGHT };

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};

byte rowPins[ROWS] = { 8, 7, 6, 5 };
byte colPins[COLS] = { 4, 3, 2 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void onKey(char key);
void onKeyDown(char key);
void onKeyUp(char key);

void sendBuffer(char *buffer);
void sendBuffer(byte *buffer, byte length);


bool work = true;
unsigned long lastSend = 0;

Direction direction = D_NONE;
Rotation rotation = R_NONE;

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif

  keypad.addEventListener(onKey);
  randomSeed(analogRead(0));

  vw_set_tx_pin(9);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
}

void loop()
{
  keypad.getKeys();

  if ((work) && (millis() - lastSend >= 50))
  {
    lastSend = millis();

    byte buffer[3];
    buffer[0] = 'i';
    buffer[1] = (byte)direction;
    buffer[2] = (byte)rotation;
    sendBuffer(buffer, 3);
  }
}

void onKey(char key)
{
  switch (keypad.key[keypad.findInList(key)].kstate)
  {
  case PRESSED:
    onKeyDown(key);
    break;
  case RELEASED:
    onKeyUp(key);
    break;
  }
}

void onKeyDown(char key)
{
#ifdef DEBUG
  Serial.print("> ");
  Serial.println(key);
#endif
  switch (key)
  {
    case '1':
      rotation = R_LEFT;
      break;
    case '3':
      rotation = R_RIGHT;
      break;

    case '2':
      direction = D_FORWARD;
      break;
    case '8':
      direction = D_BACK;
      break;

    case '4':
      direction = D_LEFT;
      break;
    case '6':
      direction = D_RIGHT;
      break;
  }
}

void onKeyUp(char key)
{
#ifdef DEBUG
  Serial.print("< ");
  Serial.println(key);
#endif
  switch (key)
  {
    case '2':
    case '8':
    case '4':
    case '6':
      direction = D_NONE;
      break;

    case '1':
    case '3':
      rotation = R_NONE;
      break;
      
    case '5':
      work = !work;

      if (!work)
      {
        byte buffer[1];
        buffer[0] = 's';
        sendBuffer(buffer, 1);
      }
      break;
  }
}




void sendBuffer(char *data)
{
  sendBuffer((byte *)data, strlen(data));
}

void sendBuffer(byte *data, byte length)
{
  byte buffer[VW_MAX_MESSAGE_LEN];

  buffer[0] = 0xFD;
  buffer[1] = 0xC9;
  
  memcpy(buffer + 2, data, length);
  
  vw_send((uint8_t *)buffer, length + 2);
  vw_wait_tx();
}












