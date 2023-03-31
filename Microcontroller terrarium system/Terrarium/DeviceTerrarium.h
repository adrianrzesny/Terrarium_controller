#pragma once
#include <Arduino.h>

class DeviceTerrarium
{
  public:
    DeviceTerrarium();
    void init(int pin);
    void on();
    void off();

  protected:
    int pin_device;

  private:
};
