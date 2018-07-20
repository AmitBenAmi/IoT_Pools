#include <Vibration_pools.h>

VibrationPools::VibrationPools(uint8_t pin)
    : pin(pin) {
}

void VibrationPools::begin() {
    pinMode(this->pin, INPUT);
}

bool VibrationPools::vibration() {
    int digital = digitalRead(this->pin);
    return (digital == HIGH);
}