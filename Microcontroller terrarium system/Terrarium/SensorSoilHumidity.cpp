#include "SensorSoilHumidity.h"

void SensorSoilHumidity::init(int pin)
{
  pin_device = pin;
}

float SensorSoilHumidity::getHumidity()
{
  return humidity;
}

void SensorSoilHumidity::refresh()
{
  if (pin_device == -1)
  {
    humidity = -1;
  }
  else
  {
    int analog_RH = 1024;

    analog_RH = analogRead(pin_device);

    humidity = (analog_RH * 100.0) / 1024.0;
  }
}
