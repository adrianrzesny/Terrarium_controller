#include "ClockArduino.h"

ClockArduino::ClockArduino()
{}

char* ClockArduino::getTime()
{
  refresh();

  sprintf(time_text, "Time - %02d:%02d:%02d", hours, minutes, seconds);

  return time_text;
}

void ClockArduino::refresh()
{
  unsigned long current_time = millis();
  hours = getHour(current_time);
  minutes = getMinutes(current_time);
  seconds = getSeconds(current_time);
}

int ClockArduino::getHour()
{
  refresh();
  return hours;
}

int ClockArduino::getMinutes()
{
  refresh();
  return minutes;
}

int ClockArduino::getSeconds()
{
  refresh();
  return seconds;
}

unsigned long ClockArduino::getHour(unsigned long mill)
{
  return mill / 1000 / 60 / 60;
}

unsigned long ClockArduino::getMinutes(unsigned long mill)
{
  return (mill - (getHour(mill) * 60 * 60 * 1000)) / 1000 / 60;
}

unsigned long ClockArduino::getSeconds(unsigned long mill)
{
  return (mill - (getMinutes(mill) * 60 * 1000) - (getHour(mill) * 60 * 60 * 1000)) / 1000;
}
