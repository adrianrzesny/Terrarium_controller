#include "DHT.h" 

class SensorTemperatureHumidityAir
{
  public:
    SensorTemperatureHumidityAir();
    void init(int pin);
    float getHumidity();
    float getTemperature();
    void refresh();

  protected:
    int pin_device = -1;
    DHT dht;

  private:
    float humidity = 0.0;
    float temperature = 0.0;
};
