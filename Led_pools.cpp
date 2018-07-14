#include <Led_pools.h>

LedPools::LedPools(uint8_t pin) {
    this->pin = pin;
}

LedPools::begin() {
    pinMode(this->pin, OUTPUT);
}

LedPools::turnOn() {
    digitalWrite(this->pin, HIGH);
}

LedPools::turnOff() {
    digitalWrite(this->pin, LOW);
}