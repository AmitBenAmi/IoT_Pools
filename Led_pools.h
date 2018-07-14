#include <stdint.h>

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef Led_pools_H
#define Led_pools_H
#endif

class LedPools {
    public:
        LedPools(uint8_t pin);
        void begin();
        void turnOn();
        void turnOff();

    private:
        uint8_t pin;
};