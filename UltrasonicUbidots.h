#include "Ultrasonic_pools.h"

#ifndef UltrasonicUbidots_h
#define UltrasonicUbidots_h
#endif

class UltrasonicUbidots {
    public:
        UltrasonicUbidots(char* ID, UltrasonicPools ultrasonicPool)
            : ID(ID),
              ultrasonicPool(ultrasonicPool) {

        }
        char* getID() {
            return this->ID;
        }
        UltrasonicPools getUltrasonicPool() {
            return this->ultrasonicPool;
        }
    
    private:
        char* ID;
        UltrasonicPools ultrasonicPool;
};