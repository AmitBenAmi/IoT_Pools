#include <Led_pools.h>
#include <Ultrasonic_pools.h>

const long CLOSE_DISTANCE_TURN_ON_LED = 15;

// Trig
uint8_t trigPin = 10;

// Echos
uint8_t redEchoPin = 6;
uint8_t yellowEchoPin = 7;
uint8_t greenEchoPin = 8;
uint8_t whiteEchoPin = 9;

// Ultrasonics
UltrasonicPools redUltrasonic(trigPin, redEchoPin, "Red");
UltrasonicPools yellowUltrasonic(trigPin, yellowEchoPin, "Yellow");
UltrasonicPools greenUltrasonic(trigPin, greenEchoPin, "Green");
UltrasonicPools whiteUltrasonic(trigPin, whiteEchoPin, "White");

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

  redUltrasonic.begin();
  yellowUltrasonic.begin();
  greenUltrasonic.begin();
  whiteUltrasonic.begin();

  redLed.begin();
  yellowLed.begin();
  greenLed.begin();
  whiteLed.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  long distanceRed, distanceYellow, distanceGreen, distanceWhite;
  
  distanceRed = redUltrasonic.getDistanceInCm();
  distanceYellow = yellowUltrasonic.getDistanceInCm();
  distanceGreen = greenUltrasonic.getDistanceInCm();
  distanceWhite = whiteUltrasonic.getDistanceInCm();

  handleLedLight(distanceRed, redLed);
  handleLedLight(distanceYellow, yellowLed);
  handleLedLight(distanceGreen, greenLed);
  handleLedLight(distanceWhite, whiteLed);

  redUltrasonic.distanceInCm(distanceRed);
  yellowUltrasonic.distanceInCm(distanceYellow);
  greenUltrasonic.distanceInCm(distanceGreen);
  whiteUltrasonic.distanceInCm(distanceWhite);
}

void handleLedLight(long distance, LedPools led) {
  if (distance <= CLOSE_DISTANCE_TURN_ON_LED) {
    led.turnOn();
  } else {
    led.turnOff();
  }
}