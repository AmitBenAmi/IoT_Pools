#include <Led_pools.h>

LedPools::LedPools(uint8_t pin) {
    this->pin = pin;
}

void LedPools::begin() {
    pinMode(this->pin, OUTPUT);
}

void LedPools::turnOn() {
    digitalWrite(this->pin, HIGH);
}

void LedPools::turnOff() {
    digitalWrite(this->pin, LOW);
}