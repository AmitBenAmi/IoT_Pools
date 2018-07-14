#include <Led_pools.h>
#include <Ultrasonic_pools.h>

const long CLOSE_DISTANCE_TURN_ON_LED = 15;

// Trigs
uint8_t redTrigPin = 2;
uint8_t yellowTrigPin = 3;
uint8_t greenTrigPin = 4;
uint8_t whiteTrigPin = 5;

// Echos
uint8_t redEchoPin = 6;
uint8_t yellowEchoPin = 7;
uint8_t greenEchoPin = 8;
uint8_t whiteEchoPin = 9;

// Ultrasonics
UltrasonicPools redUltrasonic(redTrigPin, redEchoPin, "Red");
UltrasonicPools yellowUltrasonic(yellowTrigPin, yellowEchoPin, "Yellow");
UltrasonicPools greenUltrasonic(greenTrigPin, greenEchoPin, "Green");
UltrasonicPools whiteUltrasonic(whiteTrigPin, whiteEchoPin, "White");

// Led pins
int redLedPin = 2;
int yellowLedPin = 3;
int greenLedPin = 4;
int whiteLedPin = 5;

// Leds
LedPools redLed(redLedPin);
LedPools yellowLed(yellowLedPin);
LedPools greenLed(greenLedPin);
LedPools whiteLed(whiteLedPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  redLed.begin();
  yellowLed.begin();
  greenLed.begin();
  whiteLed.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  long distanceRed, distanceYellow, distanceGreen, distanceWhite;
  
  distanceRed = redUltrasonic.distanceInCm();
  distanceYellow = yellowUltrasonic.distanceInCm();
  distanceGreen = greenUltrasonic.distanceInCm();
  distanceWhite = whiteUltrasonic.distanceInCm();

  handleLedLight(distanceRed, redLed);
  handleLedLight(distanceYellow, yellowLed);
  handleLedLight(distanceGreen, greenLed);
  handleLedLight(distanceWhite, whiteLed);

  redUltrasonic.printDistanceInCm(distanceRed);
  yellowUltrasonic.printDistanceInCm(distanceYellow);
  greenUltrasonic.printDistanceInCm(distanceGreen);
  whiteUltrasonic.printDistanceInCm(distanceWhite);
}

void handleLedLight(long distance, LedPools led) {
  if (distance <= CLOSE_DISTANCE_TURN_ON_LED) {
    led.turnOn();
  } else {
    led.turnOff();
  }
}