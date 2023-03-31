#include "SensorTemperatureHumidityAir.h"

SensorTemperatureHumidityAir::SensorTemperatureHumidityAir()
{}

void SensorTemperatureHumidityAir::init(int pin)
{
  pin_device = pin;

  dht.setup(pin_device, INPUT);
}

float SensorTemperatureHumidityAir::getHumidity()
{
  return humidity;
}

float SensorTemperatureHumidityAir::getTemperature()
{
  return temperature;
}

void SensorTemperatureHumidityAir::refresh()
{

  if (pin_device == -1)
  {
    humidity = -1;
    temperature = -1;
  }
  else
  {
    humidity = dht.getHumidity();
    temperature = dht.getTemperature();
  }
}
