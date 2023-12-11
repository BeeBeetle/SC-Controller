#include <Bounce2.h>
constexpr int NUM_BUTTONS = 0; // the number of moment buttons on the controller
Bounce buttons[NUM_BUTTONS]; // an array with the buttons in it
constexpr int NUM_TOGGLES = 2; // the number of toggle switches I'm using
constexpr int BOUNCE_INTER = 10; // the ms delay over which the bounce is checked
Bounce toggles[NUM_TOGGLES]; // sets an array with the number of toggles above

void setup ()
{
  Joystick.useManualSend(true); // manually determine if the switch gets a signal
  for (int t = 0; t < NUM_TOGGLES; t++) 
  { // loops through the toggles to assign the switch types and add the interval
    toggles[t].attach(t, INPUT_PULLUP);
    toggles[t].interval(BOUNCE_INTER);
  }
  for (int b = 0; b < NUM_BUTTONS; b++) // as above lopps through the buttons this time and adds the same items
  { // right now assumes the pins are assigned sequentially on the teensy so that the lowest pin numbers will be toggle swtiches
    buttons[b].attach(b+NUM_TOGGLES, INPUT_PULLUP); // if pin assignment varies will change the constexpr to be defined array
    buttons[b].interval(BOUNCE_INTER);
  }
}

void loop ()
{
  Joystick.hat(-1); // for some reason I had a hat input, setting -1 "resets" the hat
  for (int t = 0; t < NUM_TOGGLES; t++)
  { // loop through the toggle switches and assigning them below to a joystick buttin starting at 1
    toggles[t].update(); // check if their state (on/off) has changed
    if (toggles[t].risingEdge())
    { // if the switch turns off (going from low to high) will give a signal to the PC
      Joystick.button(t+1, 1);
    }
    else if (toggles[t].fallingEdge())
    { // if the switch turns on (going from high to low) will give a signal to the PC
      Joystick.button(t+1, 1);
    }
    else
    { // if neither are true will give no signal
      Joystick.button(t+1, 0);
    }
  }
  for (int b = 0; b < NUM_BUTTONS; b++)
  {
    buttons[b].update();
    if (buttons[b].fallingEdge())
    {
      Joystick.button(b, 1);
    }
    else
    {
      Joystick.button(b, 0);
    }
  } 
  delay(50);
  Joystick.send_now(); // sends the joystick inputs recorded in the for loop
}