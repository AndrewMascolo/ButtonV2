#include<ButtonV2.h>
ButtonV2 Button1;

const byte ButtonPin = 2;

void setup()
{
  //pinMode(LEDpin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);
  Serial.begin(115200);
  Button1.SetStateAndTime(LOW);
  Serial.println("ready");
}

void loop()
{
  byte type = Button1.CheckButton(ButtonPin); // current time and length of time to press the button as many times as you can ie. 1.5 seconds
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
}
