#include <Bounce2.h>
constexpr int NUM_TOGGLES = 2; // the number of toggle switches I'm using
constexpr int BOUNCE_INTER = 10; // the ms delay over which the bounce is checked
Bounce toggles[NUM_TOGGLES]; // sets an array with the number of toggles above

void setup ()
{
  Joystick.useManualSend(true); // manually determine if the switch gets a signal
  for (int i = 0; i < NUM_TOGGLES; i++) 
  { // loops through the toggles to assign the switch types and add the interval
    toggles[i].attach(i, INPUT_PULLUP);
    toggles[i].interval(BOUNCE_INTER);
  }
}

void loop ()
{
  Joystick.hat(-1); // for some reason I had a hat input, setting -1 "resets" the hat
  for (int i = 0; i < NUM_TOGGLES; i++)
  { // loop through the toggle switches and assigning them below to a joystick buttin starting at 1
    toggles[i].update(); // check if their state (on/off) has changed
    if (toggles[i].risingEdge())
    { // if the switch turns off (going from low to high) will give a signal to the PC
      Joystick.button(i+1, 1);
    }
    else if (toggles[i].fallingEdge())
    { // if the switch turns on (going from high to low) will give a signal to the PC
      Joystick.button(i+1, 1);
    }
    else
    { // if neither are true will give no signal
      Joystick.button(i+1, 0);
    }
  }
  delay(50);
  Joystick.send_now(); // sends the joystick inputs recorded in the for loop
}