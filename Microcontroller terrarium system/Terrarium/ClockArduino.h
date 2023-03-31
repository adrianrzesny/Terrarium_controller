#pragma once
#include "Arduino.h"

class ClockArduino
{
  public:
    ClockArduino();
    char* getTime();
    void refresh();
    int getHour();
    int getMinutes();
    int getSeconds();

  protected:
    unsigned long getHour(unsigned long mill);
    unsigned long getMinutes(unsigned long mill);
    unsigned long getSeconds(unsigned long mill);

  private:
    char time_text[8];
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
};
