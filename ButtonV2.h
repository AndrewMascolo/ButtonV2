//ButtonV2

#ifndef ButtonV2_h
#define ButtonV2_h

enum {WAITING = 0, PRESSED, DOUBLE_PRESSED, MULTI_PRESSED, HELD = 100, RELEASED};

#define SECONDS 1000000
#define MILLISECONDS 1000
#define MICROSECONDS 1

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
//just in case someone is still using old versions
#include "WProgram.h"
#endif

class ButtonV2
{
  private:
    byte 	State, lastState;
	byte 	lastButtonState;
	byte 	output, lastOut;
	byte    _P;
	unsigned long   holdTime, DBInterval,RO_Time;
	unsigned long 	time, duration, HeldTime;
	unsigned long 	lastDebounceTime;
	
    void 	(*F_Pressed)();
	void 	(*F_DPressed)();
	void 	(*F_Mult)();
    void 	(*F_Hold)();

  public:
    ButtonV2()
	{
	  output = 0; 
	  time = 0; 
	  SetHoldTime(); 
	  SetDebounceTime();
	} 

    void SetStateAndTime(byte S = HIGH, unsigned long Time = 500) // 500 gives you enough time to press the button about 3 times.
    {
      State = S; // Set the preferred state of the button. (Is the button HIGH or LOW when pressed?)
      lastButtonState = lastState = !State; //lastState should be inverted from State
	  duration = Time;
    }
	
    void SetHoldTime(unsigned long Time = 1000)
	{
	  holdTime = Time; // Set the hold time in seconds
	}
	
    void SetDebounceTime(unsigned long Time = 50)
    {
      DBInterval = Time;
    }

    void Button_Pressed(void (*P)() )
    {
      F_Pressed = P;
    }
	
	void Button_DoublePressed(void (*DP)() )
    {
      F_DPressed = DP;
    }
	
	void Button_MultiPressed(void (*MUL)() )
    {
      F_Mult = MUL;
    }
	
    void Button_Held(void (*HOLD)() )
    {
      F_Hold = HOLD;
    }
	
	int CheckButton(byte ButtonPin)
	{
	  output = 0;
	  byte button = digitalRead(ButtonPin);
	  if (button != lastButtonState)
	  {
		lastDebounceTime = millis();
		lastButtonState = button;
		time = millis();
	  }
	  
	  // Check for Rollover
      unsigned long RO_Time = millis(); // current time into RollOver variable
      if (RO_Time < time) // is the RollOver variable smaller than ontime?
        time = RO_Time; // if yes,  reset ontime to zero
		
	  while ( (millis() - time) <= duration) 
	  {
		byte button = digitalRead(ButtonPin); // read the button
		if (button != lastState) // see if the button is not held down.
		{
		  if (button == !State) // button was released
		  {
			if ((millis() - lastDebounceTime) >= DBInterval )  // button debounce, very important
			{
			  output++; // increment a counter, but only when the button is pressed then released
			  lastDebounceTime = millis(); // update the debounce time
			}
		  }
		  lastState = button; // update the buttons last state with it's new state
		}
	  }
	  
	  if(button == State && button == lastButtonState)
		if( (HeldTime = (millis() - time)) > holdTime )
		  output = HELD; 
	   
      switch (output)
      {
        case WAITING:
          break;
		  
        case PRESSED:
          if (*F_Pressed) 
            F_Pressed();
          break;
		  
        case DOUBLE_PRESSED:
          if (*F_DPressed) 
            F_DPressed();
          break;
		  
        case MULTI_PRESSED:
          if (*F_Mult)
            F_Mult();
          break;
		  
        case HELD:
          if (*F_Hold) 
            F_Hold();
          break;
      }
	  return output; // return the output count
	}
	
	// This returns the elapsed held time
    float GetHeldTime(float divisor = SECONDS)
    {
      if (divisor > 0)
        return HeldTime / divisor;
      else
        return -1;
    }
};
#endif