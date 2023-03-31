#include<stdlib.h>
#include <stdio.h>
#include "LCDIC2.h"

#include "Terrarium.h"
#include "Keyboard.h"
#include "ClockArduino.h"

LCDIC2 lcd(0x27, 20, 4); //Information about connecting a new display
Keyboard keyboard_device;
Terrarium terrarium[2];
ClockArduino clock_arduino;

char code[16];
char code_history[16];
int mode_keypad_history = 0;
int mode_keypad = 0; //0 - data terrarium, 1 - set key
unsigned long current_time = 0;
unsigned long display_time_terrarium = 0;
unsigned long display_time_type_data = 0;
unsigned long refresh_time = 0;
int number_terrarium = 0;
int number_type_data = 0;

void setup() {

  Serial.begin(9600);
  lcd.begin();
  lcd.clear();

  terrarium[0].setName("Terrarium - 01");
  terrarium[0].setWaterPumpOn("B101#");
  terrarium[0].setWaterPumpWorkNormal("B102#");
  terrarium[0].setWaterPumpOff("B100#");
  terrarium[0].setFoggerOn("C101#");
  terrarium[0].setFoggerWorkNormal("C102#");
  terrarium[0].setFoggerOff("C100#");
  terrarium[0].setVentilatorOn("D001#");
  terrarium[0].setVentilatorWorkNormal("D002#");
  terrarium[0].setVentilatorOff("D000#");
  terrarium[0].setLightingOn("BA101#");
  terrarium[0].setLightingWorkNormal("BA102#");
  terrarium[0].setLightingOff("BA100#");
  terrarium[0].setAllOn("A001#");
  terrarium[0].setAllOff("0#");
  terrarium[0].setNormalWorking("A000#");

  terrarium[0].setPinSensorSoilHumidity(A0);
  terrarium[0].setPinSensorTemperatureHumidity(52);
  terrarium[0].setPinButton_mode_on_all(28);
  terrarium[0].setPinButton_mode_off_all(30);
  terrarium[0].setPinButton_on_lighting(26);
  terrarium[0].setPinButton_off_lighting(24);
  terrarium[0].setPinFogger(35);
  terrarium[0].setPinLighting(43);
  terrarium[0].setPinVentilator(33);
  terrarium[0].setPinWaterPump(39);

  terrarium[1].setName("Terrarium - 02");
  terrarium[1].setWaterPumpOn("B201#");
  terrarium[1].setWaterPumpWorkNormal("B202#");
  terrarium[1].setWaterPumpOff("B200#");
  terrarium[1].setFoggerOn("C201#");
  terrarium[1].setFoggerWorkNormal("C202#");
  terrarium[1].setFoggerOff("C200#");
  terrarium[1].setVentilatorOn("D001#");
  terrarium[1].setVentilatorWorkNormal("D002#");
  terrarium[1].setVentilatorOff("D000#");
  terrarium[1].setLightingOn("BA101#");
  terrarium[1].setLightingWorkNormal("BA102#");
  terrarium[1].setLightingOff("BA100#");
  terrarium[1].setAllOn("A001#");
  terrarium[1].setAllOff("0#");
  terrarium[1].setNormalWorking("A000#");

  terrarium[1].setPinSensorTemperatureHumidity(10);
  terrarium[1].setPinButton_mode_on_all(28);
  terrarium[1].setPinButton_mode_off_all(30);
  terrarium[1].setPinButton_on_lighting(26);
  terrarium[1].setPinButton_off_lighting(24);
  terrarium[1].setPinFogger(37);
  terrarium[1].setPinLighting(43);
  terrarium[1].setPinVentilator(33);
  terrarium[1].setPinWaterPump(41);
}

void(* resetFunc) (void) = 0; // create a standard reset function

void loop() {
  current_time = millis();

  readKeyboard();
  viewInformation();
  refresh();
  restartSystem();
}

void readKeyboard()
{
  //read keyboard
  keyboard_device.readCode();
  strcpy(code, "-> ");
  strcat(code, keyboard_device.getCode());
  mode_keypad = keyboard_device.getMode();

  //check mode
  if (mode_keypad_history != mode_keypad)
  {
    mode_keypad_history = mode_keypad;
    lcd.clear();

    if (mode_keypad == 1)
    {
      strcpy(code, "-> ");
      lcd.setCursor(0, 0);
      lcd.print(code);
    }
  }
}

void viewInformation()
{
  //Display information depending on the mode
  if (mode_keypad == 0)
  {
    //Terrarium
    //Check whether the time to change the display text has elapsed
    if (current_time > display_time_terrarium)
    {
      display_time_terrarium = current_time + 6000;
      number_terrarium = getNextNumberTerrarium();
      refresh_time = current_time;
      display_time_type_data = current_time;
      lcd.clear();
    }

    if (current_time > display_time_type_data)
    {
      display_time_type_data = current_time + 3000;
      number_type_data = number_type_data == 0 ? 1 : 0;
    }

    if (current_time > refresh_time)
    {
      refresh_time = current_time + 1500;

      char text[80];

      //Displaying information
      lcd.setCursor(0, 0);
      lcd.print(terrarium[number_terrarium].getName());

      if (number_type_data == 0)
      {
        lcd.setCursor(0, 1);

        float temperatureAir = terrarium[number_terrarium].getTemperatureAir();
        char *tmpSign = (temperatureAir < 0) ? "-" : "";
        float tmpVal = (temperatureAir < 0) ? -temperatureAir : temperatureAir;

        int tmpInt1 = tmpVal;
        float tmpFrac = tmpVal - tmpInt1;
        int tmpInt2 = trunc(tmpFrac * 100);

        sprintf(text, "Air: T - %s%d.%02d\xDF""C", tmpSign, tmpInt1, tmpInt2);
        lcd.print(text);
      }
      else
      {
        lcd.setCursor(0, 1);


        float humidityAir = terrarium[number_terrarium].getHumidityAir();
        char *tmpSign = (humidityAir < 0) ? "-" : "";
        float tmpVal = (humidityAir < 0) ? -humidityAir : humidityAir;

        int tmpInt1 = tmpVal;
        float tmpFrac = tmpVal - tmpInt1;
        int tmpInt2 = trunc(tmpFrac * 100);

        sprintf(text, "Air: RH - %s%d.%02d%%   ", tmpSign, tmpInt1, tmpInt2);
        lcd.print(text);
      }

      if (terrarium[number_terrarium].getHumiditySoil() != -1)
      {
        lcd.setCursor(0, 2);

        float humiditySoil = terrarium[number_terrarium].getHumiditySoil();
        char *tmpSign = (humiditySoil < 0) ? "-" : "";
        float tmpVal = (humiditySoil < 0) ? -humiditySoil : humiditySoil;

        int tmpInt1 = tmpVal;
        float tmpFrac = tmpVal - tmpInt1;
        int tmpInt2 = trunc(tmpFrac * 100);

        sprintf(text, "Soil: RH - %s%d.%02d%%   ", tmpSign, tmpInt1, tmpInt2);
        lcd.print(text);
      }
    }

    lcd.setCursor(0, 3);
    lcd.print(clock_arduino.getTime());

  }
  else
  {
    //Keyboard
    if (strcmp( code, code_history ) != 0 )
    {
      lcd.setCursor(0, 0);
      lcd.print(code);

      if (strstr(keyboard_device.getCodeAccept(), "#") != NULL)
      {
        for (int i = 0; i < (sizeof(terrarium) / sizeof(terrarium[0])); i++)
        {
          terrarium[i].executeCode(keyboard_device.getCodeAccept());
        }

        lcd.clear();
        keyboard_device.refresh();
        strcpy(code, "-> ");
        lcd.setCursor(0, 0);
        lcd.print(code);
      }
    }
    strcpy(code_history, code);
  }
}

void refresh()
{
  for (int i = 0; i < (sizeof(terrarium) / sizeof(terrarium[0])); i++)
  {
    terrarium[i].refresh();
  }
}

void restartSystem()
{
  if (clock_arduino.getHour() >= 23 && clock_arduino.getMinutes() >= 59 && clock_arduino.getSeconds() >= 55)
  {
    resetFunc();
  }
}

int getNextNumberTerrarium()
{
  if ((sizeof(terrarium) / sizeof(terrarium[0])) == (number_terrarium + 1))
  {
    return 0;
  }
  else
  {
    return ++number_terrarium;
  }
}
