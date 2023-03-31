#include "DeviceTerrarium.h"

DeviceTerrarium::DeviceTerrarium()
{
  pin_device = -1;
}

void DeviceTerrarium::init(int pin)
{
  pin_device = pin;
  pinMode(pin_device, OUTPUT);
}

void DeviceTerrarium::on()
{
  if (pin_device != -1)
  {
    digitalWrite(pin_device, HIGH);
  }
}

void DeviceTerrarium::off()
{
  if (pin_device != -1)
  {
    digitalWrite(pin_device, LOW);
  }
}
