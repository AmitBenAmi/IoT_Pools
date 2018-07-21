#include "ArduinoSide.h"

char outMessage = NOTHING; 

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
	//outMessage = message;
  strcpy(outMessage,message);
 }