#include "ArduinoSide.h"
char outMessage[32] = "0";

#include "Arduino.h"

ArduinoSide::ArduinoSide(){
}

void ArduinoSide::begin(int numOfDevice){
  Wire.begin(numOfDevice);
  Wire.onRequest(ArduinoSide::requestEvent);
}

static void ArduinoSide::requestEvent(){
  Wire.write(outMessage);
}

  
void ArduinoSide::sendMessage(char* message){
  strcpy(outMessage ,message);
}