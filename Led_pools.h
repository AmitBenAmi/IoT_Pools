#include <stdint.h>

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef LED_POOLS_H
#define LED_POOLS_H

class LedPools {
    public:
        LedPools(uint8_t pin);
        void begin();
        void turnOn();
        void turnOff();

    private:
        uint8_t pin;
};