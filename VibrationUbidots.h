#include "Vibration_pools.h"

#ifndef VibrationUbidots_h
#define VibrationUbidots_h
#endif

class VibrationUbidots {
    public:
        VibrationUbidots(char* ID, VibrationPools vibrationPool)
            : ID(ID),
              vibrationPool(vibrationPool) {
        }

        char* getID() {
            return this->ID;
        }

        VibrationPools getVibrationPool() {
            return this->vibrationPool;
        }

    private:
        char* ID;
        VibrationPools vibrationPool;
};