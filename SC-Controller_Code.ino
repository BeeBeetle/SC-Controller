// below will be what is essentially an accounting of all the pins we are using on the teensy excluding potentiometers
// right now there are no actual joysticks or hats, if I decide to add one that will be coming at a later time and may or may not be tracked here
constexpr int BUTTON_PINS = 13; // the number of momentary buttons used on the teensy
// an array with the pin numbers in it: the order of the pin numbers is the button assignment order
// so the first listed pin will be joystick button 1, then 2, 3, and so on
int buttons[BUTTON_PINS] = {0,1,2,3,4,5,6,7,8,12,16,17,18}; // use the numbers for the pins you have momentary buttons on
// toggle switches or latching buttons go here, anything that you don't press and hold i.e. constant input items (non-momentary)
constexpr int TOGGLE_PINS = 6; // the number of toggle switches I'm using
int toggles[TOGGLE_PINS] = {9,10,11,19,20,21}; // list the pin numbers for all your toggle switches AND LATCHING BUTTONS (they have to be treated the same)
// it is very important that the number of zeros in the two array's below matches matches the number for TOGGLE_PINS above, otherwise you will miss buttons or be out of bounds
int toggleState[] = {0,0,0,0,0,0}; // this will be used later to track the current state of our toggled things
int lastToggleState[] = {0,0,0,0,0,0}; // same as above but to compare with the current state
// the deadzone gives us a range for which the joystick (or thumbstick) will report neutral input (centered) in the code for reading the analog pins
int deadzone = 20;
int xval;
int yval;

void setup ()
{
  Joystick.begin(); // initializes the joystick in our code
  for (int t = 0; t < TOGGLE_PINS; t++) 
  { // loops through the toggles to assign the switch types to each one (if you had lights you could do output!)
    pinMode(toggles[t], INPUT_PULLUP);
  }
  for (int b = 0; b < BUTTON_PINS; b++) // as above but loops through the buttons this time
  { // right now assumes the pins are assigned sequentially on the teensy so that the lowest pin numbers will be toggle swtiches
    pinMode(buttons[b], INPUT_PULLUP); // same as above for buttons
  }
  // we don't need to add anything here for potentiometers
}

void loop ()
{
  Joystick.hat(-1); // for some reason I was getting hat input, setting -1 "resets" the hat, of course I may add a hat later!

  // this handles the potentiometers, use the actual pin number, not the "analog" number i.e A0 or A4 (although if using an Arduino I think you do use A0 or A4)
  // by default a joystick device only has two sliders
  Joystick.sliderRight(analogRead(22)); 
  Joystick.sliderLeft(analogRead(23));
  Joystick.Y(511);
  Joystick.X(511);

  // the code below lets us implement the deadzone for a joystick as well as setting the pins
  // the pots in the thumbstick (in this case) output a reading from 0-1023 making the middle (zero user input) 511
  // xval = analogRead(21);                                       // it is important that the pins here use the actual pin number (like the sliders)
  // yval = analogRead(20);                                       // we are setting the pins with a variable so if the wiring changes we change the number in one place only
  // if ((xval > (511 - deadzone)) && (xval < (511 + deadzone)))  // checks to see if the input falls in the deadzone (set at the start) of +-20 with 511 being the middle
  // {                                                            // you want a deadzone so that unintentionally bumping the controller or thumbstick does not give an output
  //   Joystick.X(511);                                           // our "no input" value
  // } else {
  //   Joystick.X(xval);  // the actual reading should it be outside the deadzone
  // }
  // if ((yval > (511 - deadzone)) && (yval < (511 + deadzone)))  // same as above but for the Y axis
  // {
  //   Joystick.Y(511);
  // } else {
  //   Joystick.Y(yval);
  // }

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
      }
      else if (toggleState[t] == LOW)
      {
        Joystick.button(t+1, 1);
      }
    }
    // we want to make sure the states are updated so that it doesn't give output anymore after the initial flip
    lastToggleState[t] = toggleState[t];
    if (toggleState[t] == lastToggleState[t])
    { // this is more of the same from above but to ensure that we have NO input when the state of the switch hasn't changed
      if (toggleState[t] == HIGH)
      {
        Joystick.button(t+1, 0);
      }
      else if (toggleState[t] == LOW)
      {
        Joystick.button(t+1, 0);
      }
    }
  }

  // here we are taking our buttons and giving them a place on the joystick
  for (int b = 0; b < BUTTON_PINS; b++) // cycle through all our buttons
  { // same as before with the high low, but this time since we aren't tracking a state change if the button is held we get constant output
    // which is, of course, fine because anything tracked here MUST be a momentary button
    buttonState[b] = digitalRead(buttons[b]);
    if (buttonState[b] == HIGH)
    {
      Joystick.button(b+1+TOGGLE_PINS, 0);
    }
    else if (buttonState[b] == LOW)
    {
      Joystick.button(b+1+TOGGLE_PINS, 1);
    }
  }
}