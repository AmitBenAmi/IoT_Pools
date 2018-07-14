#include <stdint.h>
#include <NewPing.h>

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