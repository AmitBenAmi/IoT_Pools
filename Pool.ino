#include <Led_pools.h>
#include <UltrasonicUbidots.h>
#include <ArduinoSide.h>
#include <ConfigCodes.h>

ArduinoSide Arduino_Side;

// Ultrasonic trig pins
uint8_t redTrigPin = 5;
uint8_t yellowTrigPin = 8;
uint8_t greenTrigPin = 2;
uint8_t whiteTrigPin = 11;

// Ultrasonic echo pins
uint8_t redEchoPin = 6;
uint8_t yellowEchoPin = 9;
uint8_t greenEchoPin = 3;
uint8_t whiteEchoPin = 12;

// Led pins
int redLedPin = 7;
int yellowLedPin = 10;
int greenLedPin = 4;
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
  Arduino_Side.begin(ARDUINO_ESP8266_COMMUNICATION_ID);

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
  char code;

  if (distance <= CLOSE_DISTANCE_TURN_ON_LED) {
    led->turnOn();    
    code = DISTANCE;
  } else {
    led->turnOff();
    code = NOTHING;
  }
  
  String message = (String)code + (String)DELIMITER + (String)ubidotsId + (String)DELIMITER + (String)distance + (String)DELIMITER;
  Arduino_Side.sendMessage(message.c_str());
}