void setup ()
{
  Joystick.useManualSend(true);
  pinMode(0, INPUT_PULLUP);
}

void loop ()
{
  if (digitalRead(0) == HIGH)
  {
    Joystick.button(1, 0);
  }
  else
  {
    Joystick.button(1, 1);
  }
  delay(5);
  Joystick.send_now();
}