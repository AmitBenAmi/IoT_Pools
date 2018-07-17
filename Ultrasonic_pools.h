#include <stdint.h>

#ifndef NewPing_h
#include <NewPing.h>
#endif

#ifndef Ultrasonic_pools_h
#define Ultrasonic_pools_h
#endif

// Sonar/Ping parameters
#ifndef DELAY_BETWEEN_SONAR_PINGS
#define DELAY_BETWEEN_SONAR_PINGS 35
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