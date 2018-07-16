#include <Wire.h>
#include <string.h>
#include "ConfigCodes.h"

class ArduinoSide{
  public: 
    ArduinoSide();
    void begin(int numOfDevice);
	  static void requestEvent();
	  void sendMessage(char message);
}; 

