#include "ArduinoSide.h"

char outMessage[] = "hello"; 

ArduinoSide::ArduinoSide(){
}

void ArduinoSide::begin(int numOfDevice){
  Wire.begin(numOfDevice);
  Wire.onReceive(ArduinoSide::receiveEvent);
  Wire.onRequest(ArduinoSide::requestEvent);
}


// static char* ArduinoSide::receiveEvent(int howMany){
//   char readString[] = ""; 
//   int len = sizeof(readString)/sizeof(char) - 1;
//   while (0< Wire.available()) {
// 	char c = Wire.read(); 
// 	readString[len] = c;
//     len++;
//   }
//   return readString;
// }


static void ArduinoSide::requestEvent(){
  Wire.write(outMessage);
  }

  
 void ArduinoSide::sendMessage(char message[]){
	strcpy(outMessage, message);
 
 }