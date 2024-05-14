Welcome to my joystick code, I hope my notes are comprehensible.

To start off, in Windows 10 (as far as I can tell) a joystick is limited to the following:
   1. Three axes of motion (for an actual stick) X, Y, and Z
   2. Thirty-two buttons
   3. One hat (imagine a d-pad or thumbstick from a playstation controller)
   4. Two sliders (aka potentiometers of any kind)

Because of this if you wanted to have a dual joystick setup with fifty buttons and three potentiometers you would
need to have two teensy's working together that would register as two seperate joysticks as a default.
There are solutions to this that I am exploring, particularly https://forum.pjrc.com/index.php?threads/many-axis-joystick.23681/ 
and http://www.leobodnar.com/products/BU0836/.
However more work is needed to determine how this works exactly, if Windows will be OK with the changes or
if Windows wont care and it depends entirely on the program for which the devices is intended to be used.
