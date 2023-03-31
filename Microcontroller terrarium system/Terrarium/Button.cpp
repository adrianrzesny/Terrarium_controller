#include "Button.h"

Button::Button()
{}

void Button::setPin(int pin)
{
  pin_device = pin;
  ez_button = new ezButton(pin_device);
  ez_button->setDebounceTime(50);

  int state = ez_button->getState();
  if (state == HIGH)
  {
    isOn = false;
  }
  else
  {
    isOn = true;
  }
}

void Button::refresh()
{
  ez_button->loop();

  if (ez_button->isPressed())
  {
    isOn = true;
  }

  if (ez_button->isReleased())
  {
    isOn = false;
  }
}

int Button::getActivity()
{
  return isOn == true ? 1 : 0;
}
