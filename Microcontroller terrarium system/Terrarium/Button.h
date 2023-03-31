#pragma once
#include <ezButton.h>
#include "Arduino.h"

class Button
{
  public:
    Button();
    void setPin(int pin);
    void refresh();
    int getActivity();

  protected:

  private:
    ezButton *ez_button;
    bool isOn = false;
    int pin_device;
};
