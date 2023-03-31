#include "Fogger.h"
#include "Lighting.h"
#include "SensorSoilHumidity.h"
#include "SensorTemperatureHumidityAir.h"
#include "Ventilator.h"
#include "WaterPump.h"
#include "ClockArduino.h"
#include "Button.h"

class Terrarium
{
  public:
    Terrarium();
    Terrarium(char* name);
    void setName(char* name);
    void init();
    void setPinFogger(int pin);
    void setPinLighting(int pin);
    void setPinSensorSoilHumidity(int pin);
    void setPinSensorTemperatureHumidity(int pin);
    void setPinVentilator(int pin);
    void setPinWaterPump(int pin);
    void setPinButton_mode_on_all(int pin);
    void setPinButton_mode_off_all(int pin);
    void setPinButton_on_lighting(int pin);
    void setPinButton_off_lighting(int pin);
    void refresh();
    char* getName();
    float getHumidityAir();
    float getTemperatureAir();
    float getHumiditySoil();
    void setWaterPumpOn(char* code);
    void setWaterPumpWorkNormal(char* code);
    void setWaterPumpOff(char* code);
    void setFoggerOn(char* code);
    void setFoggerWorkNormal(char* code);
    void setFoggerOff(char* code);
    void setVentilatorOn(char* code);
    void setVentilatorWorkNormal(char* code);
    void setVentilatorOff(char* code);
    void setLightingOn(char* code);
    void setLightingWorkNormal(char* code);
    void setLightingOff(char* code);
    void setAllOn(char* code);
    void setAllOff(char* code);
    void setNormalWorking(char* code);
    void executeCode(char* code);
    void setDebug(bool value);
    void printDebug(char* text);

    const int HUMIDITY_LEVEL_ON_WATER_DEVICE = 80;
    const int HUMIDITY_LEVEL_OFF_WATER_DEVICE = 85;
    const int HUMIDITY_LEVEL_ON_VENTILATOR = 80;

  protected:
    Fogger fogger;
    Lighting lighting;
    Ventilator ventilator;
    WaterPump waterPump;
    SensorSoilHumidity sensorSoilHumidity;
    SensorTemperatureHumidityAir sensorTemperatureHumidityAir;
    ClockArduino clockArduino;

  private:
    bool debug = false;
    float temperature = 0.0;
    float humidity = 0.0;
    char name_terrarium[16];
    char code_water_pump_on[16];
    char code_water_pump_work_normal[16];
    char code_water_pump_off[16];
    char code_fogger_on[16];
    char code_fogger_work_normal[16];
    char code_fogger_off[16];
    char code_ventilator_on[16];
    char code_ventilator_work_normal[16];
    char code_ventilator_off[16];
    char code_lighting_on[16];
    char code_lighting_work_normal[16];
    char code_lighting_off[16];
    char code_all_on[16];
    char code_all_off[16];
    char code_normal_working[16];

    int workWaterPump = 2; //0-off, 1-on, 2-normal
    int workFogger = 2; //0-off, 1-on, 2-normal
    int workVentilator = 2; //0-off, 1-on, 2-normal
    int workLighting = 2; //0-off, 1-on, 2-normal

    Button button_mode_on_all;
    Button button_mode_off_all;
    Button button_on_lighting;
    Button button_off_lighting;

    void readStatusButton();
    void setStatusWaterPump();
    void setStatusFogger();
    void setStatusVentilator();
    void setStatusLighting();

};
