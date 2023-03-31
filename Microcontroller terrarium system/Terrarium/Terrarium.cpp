#include "Terrarium.h"

Terrarium::Terrarium()
{
  strcpy(name_terrarium, "Bez nazwy");
}

Terrarium::Terrarium(char* name)
{
  strcpy(name_terrarium, name);
}

void Terrarium::setName(char* name)
{
  strcpy(name_terrarium, name);
}

void Terrarium::init()
{}

void Terrarium::setPinFogger(int pin)
{
  fogger.init(pin);
  workFogger = 2;
}

void Terrarium::setPinLighting(int pin)
{
  lighting.init(pin);
  workLighting = 1;
}

void Terrarium::setPinSensorSoilHumidity(int pin)
{
  sensorSoilHumidity.init(pin);
}

void Terrarium::setPinSensorTemperatureHumidity(int pin)
{
  sensorTemperatureHumidityAir.init(pin);
}

void Terrarium::setPinVentilator(int pin)
{
  ventilator.init(pin);
  workVentilator = 2;
}

void Terrarium::setPinWaterPump(int pin)
{
  waterPump.init(pin);
  workWaterPump = 2;
}

void Terrarium::setPinButton_mode_on_all(int pin)
{
  button_mode_on_all.setPin(pin);
}

void Terrarium::setPinButton_mode_off_all(int pin)
{
  button_mode_off_all.setPin(pin);
}

void Terrarium::setPinButton_on_lighting(int pin)
{
  button_on_lighting.setPin(pin);
}

void Terrarium::setPinButton_off_lighting(int pin)
{
  button_off_lighting.setPin(pin);
}

void Terrarium::refresh()
{
  button_mode_on_all.refresh();
  button_mode_off_all.refresh();
  button_on_lighting.refresh();
  button_off_lighting.refresh();

  readStatusButton();
  
  setStatusWaterPump();
  setStatusFogger();
  setStatusVentilator();
  setStatusLighting();
}

char* Terrarium::getName()
{
  return name_terrarium;
}

float Terrarium::getHumidityAir()
{
  sensorTemperatureHumidityAir.refresh();
  humidity = sensorTemperatureHumidityAir.getHumidity() != 0 ? sensorTemperatureHumidityAir.getHumidity() : 0;
  return humidity;
}

float Terrarium::getTemperatureAir()
{
  sensorTemperatureHumidityAir.refresh();
  temperature = sensorTemperatureHumidityAir.getTemperature() != 0 ? sensorTemperatureHumidityAir.getTemperature() : temperature;
  return temperature;
}

float Terrarium::getHumiditySoil()
{
  sensorSoilHumidity.refresh();
  return sensorSoilHumidity.getHumidity();
}

void Terrarium::setWaterPumpOn(char* code)
{

  strcpy(code_water_pump_on, code);
}

void Terrarium::setWaterPumpWorkNormal(char* code)
{

  strcpy(code_water_pump_work_normal, code);
}

void Terrarium::setWaterPumpOff(char* code)
{

  strcpy(code_water_pump_off, code);
}

void Terrarium::setFoggerOn(char* code)
{

  strcpy(code_fogger_on, code);
}

void Terrarium::setFoggerWorkNormal(char* code)
{

  strcpy(code_fogger_work_normal, code);
}

void Terrarium::setFoggerOff(char* code)
{

  strcpy(code_fogger_off, code);
}

void Terrarium::setVentilatorOn(char* code)
{

  strcpy(code_ventilator_on, code);
}

void Terrarium::setVentilatorWorkNormal(char* code)
{

  strcpy(code_ventilator_work_normal, code);
}

void Terrarium::setVentilatorOff(char* code)
{

  strcpy(code_ventilator_off, code);
}

void Terrarium::setLightingOn(char* code)
{

  strcpy(code_lighting_on, code);
}

void Terrarium::setLightingWorkNormal(char* code)
{

  strcpy(code_lighting_work_normal, code);
}

void Terrarium::setLightingOff(char* code)
{

  strcpy(code_lighting_off, code);
}

void Terrarium::setAllOn(char* code)
{
  strcpy(code_all_on, code);
}

void Terrarium::setAllOff(char* code)
{
  strcpy(code_all_off, code);
}

void Terrarium::setNormalWorking(char* code)
{
  strcpy(code_normal_working, code);
}

void Terrarium::executeCode(char* code)
{
  if (strcmp( code, code_water_pump_on ) == 0)
  {
    workWaterPump = 1;
  }
  else if (strcmp( code, code_water_pump_work_normal ) == 0)
  {
    workWaterPump = 2;
  }
  else if (strcmp( code, code_water_pump_off ) == 0)
  {
    workWaterPump = 0;
  }
  else if (strcmp( code, code_fogger_on ) == 0)
  {
    workFogger = 1;
  }
  else if (strcmp( code, code_fogger_work_normal ) == 0)
  {
    workFogger = 2;
  }
  else if (strcmp( code, code_fogger_off ) == 0)
  {
    workFogger = 0;
  }
  else if (strcmp( code, code_ventilator_on ) == 0)
  {
    workVentilator = 1;
  }
  else if (strcmp( code, code_ventilator_work_normal ) == 0)
  {
    workVentilator = 2;
  }
  else if (strcmp( code, code_ventilator_off ) == 0)
  {
    workVentilator = 0;
  }
  else if (strcmp( code, code_lighting_on ) == 0)
  {
    workLighting = 1;
  }
  else if (strcmp( code, code_lighting_work_normal ) == 0)
  {
    workLighting = 2;
  }
  else if (strcmp( code, code_lighting_off ) == 0)
  {
    workLighting = 0;
  }
  else if (strcmp( code, code_all_on ) == 0)
  {
    workWaterPump = 1;
    workFogger = 1;
    workVentilator = 1;
    workLighting = 1;
  }
  else if (strcmp( code, code_normal_working ) == 0)
  {
    workWaterPump = 2;
    workFogger = 2;
    workVentilator = 2;
    workLighting = 2;
  }
  else if (strcmp( code, code_all_off ) == 0)
  {
    workWaterPump = 0;
    workFogger = 0;
    workVentilator = 0;
    workLighting = 0;
  }
}

void Terrarium::setDebug(bool value)
{
  debug = value;
}

void Terrarium::printDebug(char* text)
{
  Serial.print(getName());
  Serial.print(" - ");
  Serial.println(text);
}


void Terrarium::readStatusButton()
{
  if (button_mode_on_all.getActivity() == 1)
  {
    workWaterPump = 1;
    workFogger = 1;
    workVentilator = 1;
    workLighting = 1;
  }

  if (button_mode_off_all.getActivity() == 1)
  {
    workWaterPump = 0;
    workFogger = 0;
    workVentilator = 0;
    workLighting = 0;
  }

  if (button_on_lighting.getActivity() == 1)
  {
    workLighting = 1;
  }

  if (button_off_lighting.getActivity() == 1)
  {
    workLighting = 0;
  }
}

void Terrarium::setStatusWaterPump()
{
  switch (workWaterPump)
  {
    case 0:
      waterPump.off();
      if (debug)
      {
        printDebug("WaterPumpOFF");
      }
      break;
    case 1:
      waterPump.on();
      if (debug)
      {
        printDebug("WaterPumpON");
      }
      break;
    case 2:
      int hour = clockArduino.getHour();
      int minutes = clockArduino.getMinutes();
      float humidity = sensorTemperatureHumidityAir.getHumidity();

      if ((minutes < 5 && humidity > 0 && humidity < HUMIDITY_LEVEL_ON_WATER_DEVICE)
          || (minutes >= 30 && minutes <= 40 && (hour == 0 || hour == 12)))
      {
        waterPump.on();
      }
      else
      {
        if (minutes < 5)
        {
          if (humidity > HUMIDITY_LEVEL_OFF_WATER_DEVICE)
          {
            waterPump.off();
          }
        }
        else
        {
          waterPump.off();
        }
      }

      if (debug)
      {
        printDebug("WaterPumpNormal");
      }
      break;
  }

}

void Terrarium::setStatusFogger()
{
  switch (workFogger)
  {
    case 0:
      fogger.off();
      if (debug)
      {
        printDebug("FoggerOFF");
      }
      break;
    case 1:
      fogger.on();
      if (debug)
      {
        printDebug("FoggerON");
      }
      break;
    case 2:
      int hour = clockArduino.getHour();
      int minutes = clockArduino.getMinutes();
      float humidity = sensorTemperatureHumidityAir.getHumidity();

      if ((minutes < 5 && humidity > 0 && humidity < HUMIDITY_LEVEL_ON_WATER_DEVICE)
          || (minutes >= 32 && minutes <= 40 && (hour == 0 || hour == 12)))
      {
        fogger.on();
      }
      else
      {
        if (minutes < 5)
        {
          if (humidity > HUMIDITY_LEVEL_OFF_WATER_DEVICE)
          {
            fogger.off();
          }
        }
        else
        {
          fogger.off();
        }
      }

      if (debug)
      {
        printDebug("FoggerNormal");
      }
      break;
  }
}

void Terrarium::setStatusVentilator()
{
  switch (workVentilator)
  {
    case 0:
      ventilator.off();
      if (debug)
      {
        printDebug("VentilatorOFF");
      }
      break;
    case 1:
      ventilator.on();
      if (debug)
      {
        printDebug("VentilatorON");
      }
      break;
    case 2:
      int hour = clockArduino.getHour();
      int minutes = clockArduino.getMinutes();
      float humidity = sensorTemperatureHumidityAir.getHumidity();

      if ((humidity != 0.0 && humidity > HUMIDITY_LEVEL_ON_VENTILATOR && minutes >= 20 && minutes <= 30)
          || (minutes >= 32 && minutes <= 42 && (hour == 0 || hour == 12))
          || minutes == 15 || minutes == 30 || minutes == 45 )
      {
        ventilator.on();
      }
      else
      {
        ventilator.off();
      }

      if (debug)
      {
        printDebug("VentilatorNormal");
      }
      break;
  }
}

void Terrarium::setStatusLighting()
{
  switch (workLighting)
  {
    case 0:
      lighting.off();
      if (debug)
      {
        printDebug("LightOFF");
      }
      break;
    case 1:
      lighting.on();
      if (debug)
      {
        printDebug("LightON");
      }
      break;
    case 2:
      if (debug)
      {
        printDebug("LightNormal");
      }
      break;
  }
}
