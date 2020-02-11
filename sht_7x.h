 
#ifndef sht_7x_h
#define sht_7x_h
#include "Arduino.h"

class SHT_7x{
    enum Accuracy {low, high };
    private:
        uint8_t sck,sda;
        uint8_t checksum=0;
        Accuracy accuracy=Accuracy::high;
        void start();
        void clock();
        bool sendCommand(uint8_t sh_cmd);
        uint16_t getReadout();
    public:

        SHT_7x(uint8_t sck_pin, uint8_t data_pin);
        bool setAccuracy(Accuracy a);
        void init();
        float getHumidity();
        float getTemperature();
};

#endif
