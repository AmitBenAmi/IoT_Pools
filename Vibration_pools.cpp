#include <Vibration_pools.h>

VibrationPools::VibrationPools(uint8_t pin)
    : pin(pin) {
}

VibrationPools::begin() {
    pinMode(this->pin, INPUT);
}

VibrationPools::vibration() {
    int digital = digitalRead(this->pin);
    return (digital == HIGH);
}