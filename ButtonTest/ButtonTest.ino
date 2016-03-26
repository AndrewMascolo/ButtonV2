#include<ButtonV2.h>

#define numOfButtons 2
ButtonV2 buttonArray[numOfButtons];

const byte ButtonPins[numOfButtons] = {2, 3};

void setup()
{
  //pinMode(LEDpin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
  Serial.begin(115200);
  for(byte n = 0; n < numOfButtons; n++)
    buttonArray[n].SetStateAndTime(LOW);
  Serial.println("ready");
}

void loop()
{
  static byte i = 0;
  
  byte type = buttonArray[i].CheckButton(ButtonPins[i]); // current time and length of time to press the button as many times as you can ie. 1.5 seconds
  switch (type)
  {
    case WAITING:
      break;
    case PRESSED:
      Serial.println("pressed 1 time");
      break;
    case DOUBLE_PRESSED:
      Serial.println("pressed 2 times");
      break;
    case MULTI_PRESSED:
      Serial.println("pressed 3 times");
      break;
    case HELD:
      Serial.println("Button HELD");
      break;
  }
  
  i++; 
  if(i > (numOfButtons - 1) )
    i = 0;
}
