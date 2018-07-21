#include <Led_pools.h>
#include <UltrasonicUbidots.h>
#include <ArduinoSide.h>
#include <ConfigCodes.h>

const long CLOSE_DISTANCE_TURN_ON_LED = 15;
ArduinoSide Arduino_Side;

// Ultrasonic trig pins
uint8_t redTrigPin = 2;
uint8_t yellowTrigPin = 3;
uint8_t greenTrigPin = 4;
uint8_t whiteTrigPin = 5;

// Ultrasonic echo pins
uint8_t redEchoPin = 6;
uint8_t yellowEchoPin = 7;
uint8_t greenEchoPin = 8;
uint8_t whiteEchoPin = 9;

// Led pins
int redLedPin = 10;
int yellowLedPin = 11;
int greenLedPin = 12;
int whiteLedPin = 13;

// Structure for better code
struct PoolSensor {
  UltrasonicUbidots ultrasonicUbidots;
  LedPools led;
};

PoolSensor sensors[] = {
  { UltrasonicUbidots(RED_ULTRASONIC_UBIDOTS_VARIABLE_ID, UltrasonicPools(redTrigPin, redEchoPin, "Red")), LedPools(redLedPin) },
  { UltrasonicUbidots(YELLOW_ULTRASONIC_UBIDOTS_VARIABLE_ID, UltrasonicPools(yellowTrigPin, yellowEchoPin, "Yellow")), LedPools(yellowLedPin) },
  { UltrasonicUbidots(GREEN_ULTRASONIC_UBIDOTS_VARIABLE_ID, UltrasonicPools(greenTrigPin, greenEchoPin, "Green")), LedPools(greenLedPin) },
  { UltrasonicUbidots(WHITE_ULTRASONIC_UBIDOTS_VARIABLE_ID, UltrasonicPools(whiteTrigPin, whiteEchoPin, "White")), LedPools(whiteLedPin) }
};

int sensorsCount = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Arduino_Side.begin(8);

  sensorsCount = sizeof(sensors)/sizeof(sensors[0]);

  for (int i = 0; i < sensorsCount; i++) {
    sensors[i].led.begin();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < sensorsCount; i++) {
    long distance = sensors[i].ultrasonicUbidots.getUltrasonicPool().distanceInCm();
    handleLedLight(distance, &sensors[i].led, sensors[i].ultrasonicUbidots.getID());
    sensors[i].ultrasonicUbidots.getUltrasonicPool().printDistanceInCm(distance);
  }
}

void handleLedLight(long distance, LedPools* led, char* ubidotsId) {
  if (distance <= CLOSE_DISTANCE_TURN_ON_LED) {
    led->turnOn();
    Arduino_Side.sendMessage(((String)DISTANCE + DELIMITER + ubidotsId).c_str());
  } else {
    led->turnOff();
    Arduino_Side.sendMessage(((String)NOTHING + DELIMITER + ubidotsId).c_str());
  }
}