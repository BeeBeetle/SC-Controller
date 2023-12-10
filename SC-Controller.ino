int buttonState = 0;

void setup ()
{
  Joystick.useManualSend(true);
  Serial.begin(38400);
  pinMode(0, INPUT_PULLUP);
}

void loop ()
{
  if (digitalRead(0) == HIGH)
  {
    if (buttonState == 1)
    {
      Joystick.button(1, 1);
      buttonState = 0;
    }
    else
    {
      Joystick.button(1, 0);
    }
  }
  else
  {
    if (buttonState == 0)
    {
      Joystick.button(1, 1);
      buttonState = 1;
    }
    else
    {
      Joystick.button(1, 0);
    }
  }
  delay(100);
  Joystick.send_now();
}