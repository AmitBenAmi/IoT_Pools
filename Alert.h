#ifndef ALERT_H
#define ALERT_H

#ifndef BlynkSimpleEsp8266.h
#include <BlynkSimpleEsp8266.h>
#endif

#include <Wire.h>
#include "ConfigCodes.h"

class Alert{
	public: 
		Alert();
		void begin();
		String requestFromArduino(int numOfDevice, int lengthData);
		void start();
		void sendNotification(char* message);
		bool getPowerOn();
		bool getNotificationOn();
		void setPowerOn(bool value);
		void setNotificationOn(bool value); 
		void setNotificationBtnOn();
		void setPowerBtnOn();
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
 Blynk.begin(BLYNK_TOKEN, WIFI_SSID, WIFI_PASS);
 Blynk.virtualWrite(V1,1);
 Blynk.virtualWrite(V0,0);
}

String Alert::requestFromArduino(int numOfDevice, int lengthData){
  char readString[lengthData + 1]; 
  int len = 0;
  Wire.requestFrom(numOfDevice,lengthData);
  while(Wire.available()) {
    readString[len] = Wire.read(); 
	len++;
  }
  readString[len] = '\0';

  return (String)readString;
}

void Alert::start(){
   Blynk.run();
}

void Alert::sendNotification(char* message){
	Blynk.email("daniellezror@gmail.com", "Alert", message);
	Blynk.notify(message);
}
	
bool Alert::getPowerOn(){
	return isPowerOn;
}

bool Alert::getNotificationOn(){
	return isNotificationOn;
}

void Alert::setPowerOn(bool value){
	isPowerOn = value;
}	
	
void Alert::setNotificationOn(bool value){
	isNotificationOn = value;
}


void Alert::setNotificationBtnOn(){
	Blynk.virtualWrite(V0,1);
	isNotificationOn = true;
}

void Alert::setPowerBtnOn(){
	Blynk.virtualWrite(V1,1);
	isPowerOn = true;
}


char* Alert::CodeToMessage(char code){
	if(code == POOL) {
		return "Alert! Someone fell to the pool";
	}
	else if (code == DISTANCE) {
		return "Alert! Someone is near the pool";
	}
}