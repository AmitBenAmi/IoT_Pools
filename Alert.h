#ifndef ALERT_H
#define ALERT_H

#ifndef BlynkSimpleEsp8266.h
#include <BlynkSimpleEsp8266.h>
#endif

#include <Wire.h>
#include "ConfigCodes.h"

char auth[] = "21eb6f4db2ed43edb67f7bd376454a75";
char ssid[] = "zror1";
char pass[] = "aabbcc1234";

class Alert{
	public: 
		Alert();
		void begin();
		char requestFromArduino(int numOfDevice, int lengthData);
		void start();
		void sendNotification(char* message);
		bool get_isPowerOn();
		bool get_isNotificationOn();
		void set_isPowerOn(bool value);
		void set_isNotificationOn(bool value); 
		void set_NotificationBtnOn();
		char* CodeToMessage(char code);

  private:
		bool isPowerOn = true;
		bool isNotificationOn = false;

};

#endif

Alert::Alert(){
}

void Alert::begin(){
 Wire.begin(D1, D2);
 Blynk.begin(auth, ssid, pass);
 Blynk.virtualWrite(V1,1);
 Blynk.virtualWrite(V0,0);
}

char Alert::requestFromArduino(int numOfDevice, int lengthData){
  char readString; 
  int len = sizeof(readString)/sizeof(char) - 1;
  Wire.requestFrom(numOfDevice,lengthData);
  while(Wire.available()) {
    readString = Wire.read(); 
  }
  return readString;
}

void Alert::start(){
   Blynk.run();
}

void Alert::sendNotification(char* message){
	Blynk.email("daniellezror@gmail.com", "Alert", message);
	Blynk.notify(message);
}
	
bool Alert::get_isPowerOn(){
	return isPowerOn;
}

bool Alert::get_isNotificationOn(){
	return isNotificationOn;
}

void Alert::set_isPowerOn(bool value){
	isPowerOn = value;
}	
	
void Alert::set_isNotificationOn(bool value){
	isNotificationOn = value;
}


void Alert::set_NotificationBtnOn(){
	Blynk.virtualWrite(V0,1);
	isNotificationOn = true;
}


char* Alert::CodeToMessage(char code){
	if(code == POOL) {
		return "Alert! Someone fell to the pool";
	}
	else if (code == DISTANCE) {
		return "Alert! Someone is near the pool";
	}
}