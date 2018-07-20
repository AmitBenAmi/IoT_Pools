#include <stdint.h>

#ifndef Arduino_h
#include <Arduino.h>
#endif

#ifndef Vibration_pools_H
#define Vibration_pools_H
#endif

class VibrationPools {
    public:
        VibrationPools(uint8_t pin);
        void begin();
        bool vibration();
    
    private:
        uint8_t pin;
};