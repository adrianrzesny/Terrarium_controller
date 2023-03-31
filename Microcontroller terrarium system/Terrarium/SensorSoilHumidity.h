#include "Arduino.h"

class SensorSoilHumidity
{
    public:
		void init(int pin);
		float getHumidity();
		void refresh();
	
    protected:
		int pin_device = -1;	

    private:
		float humidity = 0.0;
};
