Welcome to my joystick code, I hope my notes are comprehensible.

To start, with a Teensy, by default, a joystick is limited to the following:
   1. Three axes of motion (for an actual stick) X, Y, and Z
   2. Thirty-two buttons
   3. One hat (imagine a d-pad or thumbstick from a playstation controller but 8 directions)
   4. Two sliders (aka potentiometers of any kind)

Because of this if you wanted to have a dual joystick setup with fifty buttons and three potentiometers you would
need to modify the code for the joystick library so that the teensy could properly communicate the additions to Windows.
There are solutions for this that I am exploring, particularly https://forum.pjrc.com/index.php?threads/many-axis-joystick.23681/ 
and http://www.leobodnar.com/products/BU0836/.
However more work is needed to determine how this works exactly, if Windows will be OK with the changes or
if Windows wont care and it depends entirely on the Teensy itself.
