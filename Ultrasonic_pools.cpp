#include <Ultrasonic_pools.h>

UltrasonicPools::UltrasonicPools(uint8_t trigPin, uint8_t echoPin, char* color) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    this->color = color;
}

void UltrasonicPools::begin() {
    this->sonar = new NewPing(this->trigPin, this->echoPin);
}

long UltrasonicPools::distanceInCm() {
    delay(DELAY_BETWEEN_SONAR_PINGS);
    return this->sonar->ping_cm();
}

void UltrasonicPools::printDistanceInCm(long distance) {
    Serial.print("Distance ");
    Serial.print(this->color);
    Serial.print(" is: ");
    Serial.print(distance);
    Serial.println("cm");
}