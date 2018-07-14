class LedPools {
    public:
        LedPools(uint8_t pin);
        void begin();
        void turnOn();
        void turnOff();

    private:
        uint8_t pin;
};