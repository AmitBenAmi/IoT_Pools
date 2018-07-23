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
Serial.println("llll");
  Serial.println(outMessage);
  Serial.println("ll22");
  Wire.write("2_5b5337acc03f9758774e5019_8_");
  Serial.println("l33l");
  
}

  
void ArduinoSide::sendMessage(char* message){
  strcpy(outMessage ,message);
}