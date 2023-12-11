#include <Bounce2.h>
constexpr int NUM_TOGGLES = 2;
constexpr int BOUNCE_INTER = 10;
Bounce toggles[NUM_TOGGLES];

void setup ()
{
  Joystick.useManualSend(true);  
  for (int i = 0; i < NUM_TOGGLES; i++)
  {
    toggles[i].attach(i, INPUT_PULLUP);
    toggles[i].interval(BOUNCE_INTER);
  }
}

void loop ()
{
  Joystick.hat(-1);
  for (int i = 0; i < NUM_TOGGLES; i++)
  {
    toggles[i].update();
    if (toggles[i].risingEdge())
    {
      Joystick.button(i+1, 1);
    }
    else if (toggles[i].fallingEdge())
    {
      Joystick.button(i+1, 1);
    }
    else
    {
      Joystick.button(i+1, 0);
    }
  }
  delay(50);
  Joystick.send_now();
}