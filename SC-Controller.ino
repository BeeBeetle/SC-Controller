// Welcome to my joystick code, I hope my notes are comprehensible
// To start off a in Windows 10 (as far as I can tell) a joystick is limited to the following:
// 1. Three axes of motion (for an actual stick) X, Y, and Z
// 2. Thirty-two buttons
// 3. One hat (imagine a d-pad or thumbstick from a playstation controller)
// 4. Two sliders (aka potentiometers of any kind)
// Because of this if you wanted to have a dual joystick setup with fifty buttons and three potentiometers you would
// need to have two teensy's working together that would register as two seperate joysticks.
// It may be possible to convince Windows that one teensy's is actually two separate devices but I have not
// investigated that. In fact it probably is possible somewhere in the joystick methods but if it is doable that
// is an issue to be tackled later.

// below will be what is essentially an accounting of all the pins we are using on the teensy excluding potentiometers
// right now there are no actual joysticks or hats, if I decide to add one that will be coming at a later time and may or may not be tracked here
constexpr int BUTTON_PINS = 3; // the number of momentary buttons used on the teensy
// an array with the pin numbers in it: the order of the pin numbers is the button assignment order
// so the first listed pin will be joystick button 1, then 2, 3, and so on
int pins[BUTTON_PINS] = {3,8,9}; // use the numbers for the pins you have momentary buttons on
// toggle switches or latching buttons go here, anything that you don't press and hold i.e. constant input items (non-momentary)
constexpr int TOGGLE_PINS = 3; // the number of toggle switches I'm using
int toggles[TOGGLE_PINS] = {2,6,7}; // list the pin numbers for all your toggle switches AND LATCHING BUTTONS (they have to be treated the same)
// it is very important that the number of entries in the two array's below matches matches the number for TOGGLE_PINS above, otherwise you will miss buttons or be out of bounds
int toggleState[] = {0,0,0}; // this will be used later to track the current state of our toggled things
int lastToggleState[] = {0,0,0}; // same as above but to compare with the current state

void setup ()
{
  Joystick.begin(); // initializes the joystick in our code
  for (int t = 0; t < TOGGLE_PINS; t++) 
  { // loops through the toggles to assign the switch types to each one (if you had lights you could do output!)
    pinMode(toggles[t], INPUT_PULLUP);
  }
  for (int b = 0; b < BUTTON_PINS; b++) // as above but loops through the buttons this time
  { // right now assumes the pins are assigned sequentially on the teensy so that the lowest pin numbers will be toggle swtiches
    pinMode(pins[b], INPUT_PULLUP); // same as above for buttons
  }
  // we don't need to add anything here for potentiometers
}

void loop ()
{
  Joystick.hat(-1); // for some reason I was getting hat input, setting -1 "resets" the hat, of course I may add a hat later!

  // this handles the potentiometers, you can only have 2 per joystick because we use the sliders for them
  Joystick.sliderLeft(analogRead(20)); // use the actual pin number, not the "analog" number i.e A0 or A4 (this can be left or right doesn't matter)

  for (int t = 0; t < TOGGLE_PINS; t++)
  { // this is for our toggle switches, we only want them to trigger when they switch because games usually only take a single input (was a key pressed or not)
    // we will track this with the two variables declared before the setup code as we loop through the number of toggles defined at the start
    toggleState[t] = digitalRead(toggles[t]); // so this will set the initial state for each toggle, although for switches (if you want immersion) make sure they are
    // in the "off" position before doing something where you flip them, otherwsie they will be "on" when they should be "off" and vice versa (they still work though)
    if (toggleState[t] != lastToggleState[t]) // we know here that if the states are different that means that the switch is in a new state
    { // differentiating between high (off) and low (on) makes sure that no matter how the switch is flipped it gives us output
      if (toggleState[t] == HIGH)
      {
        Joystick.button(t+1, 1);
        delay(50);
      }
      else if (toggleState[t] == LOW)
      {
        Joystick.button(t+1, 1);
        delay(50);
      }
      delay(50);
    }
    // we want to make sure the states are updated so that it doesn't give output anymore after the initial flip
    lastToggleState[t] = toggleState[t];
    if (toggleState[t] == lastToggleState[t])
    { // this is more of the same from above but to ensure that we have NO input when the state of the switch hasn't changed
      if (toggleState[t] == HIGH)
      {
        Joystick.button(t+1, 0);
        delay(50);
      }
      else if (toggleState[t] == LOW)
      {
        Joystick.button(t+1, 0);
        delay(50);
      }   
      delay(50);
    }
  }

  // here we are taking our buttons and giving them a place on the joystick
  for (int b = 0; b < BUTTON_PINS; b++) // cycle through all our buttons
  { // same as before with the high low, but this time since we aren't tracking a state change if the button is held we get constant output
    // which is, of course, fine because anything tracked here MUST be a momentary button
    if (digitalRead(pins[b]) == LOW)
    { // the reason to add an additional 1 here beyond the toggles is because the Arduino IDE doesn't like b=1; b <= PIN_NUMBERS      
      // and with the 1 we ensure that the button assignment STARTS at 1 (the lowest on the joystick) and then we add the toggles
      // so with 5 toggles the first button would be on 6
      Joystick.button(b+1+TOGGLE_PINS, 1);
    }
    else
    {
      Joystick.button(b+1+TOGGLE_PINS, 0);
    }
  } 
  delay(50); // a nice bit of delay just for fun
}