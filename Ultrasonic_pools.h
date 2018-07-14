#include <stdint.h>

#ifndef NewPing_h
#include <NewPing.h>
#endif

#ifndef ULTRASONIC_POOLS_H
#define ULTRASONIC_POOLS_H

// Sonar/Ping parameters
#ifndef DELAY_BETWEEN_SONAR_PINGS
#define DELAY_BETWEEN_SONAR_PINGS 50
#endif

class UltrasonicPools {
    public:
        UltrasonicPools(uint8_t trigPin, uint8_t echoPin, char* color);
        long distanceInCm();
        void printDistanceInCm(long distance);

    private:
        uint8_t trigPin;
        uint8_t echoPin;
        char* color;
        NewPing sonar;
};