#include <VirtualWire.h>

#define KEY_TOP 0
#define KEY_LEFT 1
#define KEY_CENTER 2
#define KEY_RIGHT 3
#define KEY_BOTTOM 4
#define KEY_LOCK 5


void sendMessage(char command,char *params)
{
  String strMsg = "z ";
  strMsg += command;
  strMsg += " ";
  strMsg += params;
  strMsg += " ";
  
  char msg[255];
  
  strMsg.toCharArray(msg,255);
  
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
};

bool Buttons[6];

void readButtons()
{
  for (uint8_t i = 0; i < 6; i++)
  {
    Buttons[i] = digitalRead(i + 2);
  };
};

void setup(void)
{
  Serial.begin(9600);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  
  for (uint8_t i = 0; i < 6; i++)
  {
    pinMode(i + 2,INPUT);
    Buttons[i] = false;
  };
};

void loop(void)
{
  readButtons();
  
  if (Buttons[KEY_CENTER])
    sendMessage('h',"1");
  else if (Buttons[KEY_LOCK])
    sendMessage('h',"2");
  else if (Buttons[KEY_TOP])
    sendMessage('g',"1");
  else if (Buttons[KEY_BOTTOM])
    sendMessage('g',"2");
  else if (Buttons[KEY_LEFT])
    sendMessage('r',"1");
  else if (Buttons[KEY_RIGHT])
    sendMessage('r',"2");
  else
    sendMessage('o',"s");
};








