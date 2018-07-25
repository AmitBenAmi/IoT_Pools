#include <Alert.h>
#include <VibrationUbidots.h>
#include <UbidotsMicroESP8266.h>

// Ubidots vibration IDs
char* d6VibrationUbidots = "5b5337c2c03f9758774e5039";
char* d7VibrationUbidots = "5b5337c8c03f9758774e503c";

VibrationUbidots vibrations[] = {
  { VibrationUbidots(d6VibrationUbidots, VibrationPools(D6)) },
  { VibrationUbidots(d7VibrationUbidots, VibrationPools(D7)) }
};

int sensorsCount = 0;

char dataFromArduino[ARDUINO_ESP8266_COMMUNICATION_REQUEST_LENGTH];
char CurrentArduinoCode;
char* sensorVariableId;
float distance;
char LastArduinoCode;
Alert Alert;

Ubidots client(UBIDOTS_TOKEN);

void setup() {
  Serial.begin(9600);
  Alert.begin();
  client.wifiConnection(WIFI_SSID,WIFI_PASS);
  sensorsCount = sizeof(vibrations)/sizeof(vibrations[0]);

  for (int i = 0; i < sensorsCount; i++) {
    vibrations[i].getVibrationPool().begin();
  }
}

void loop() {
  Alert.start();
  Alert.requestFromArduino(8, ARDUINO_ESP8266_COMMUNICATION_REQUEST_LENGTH).toCharArray(dataFromArduino, ARDUINO_ESP8266_COMMUNICATION_REQUEST_LENGTH);
  CurrentArduinoCode = strtok(dataFromArduino, "_")[0];
  sensorVariableId = strtok(NULL, "_");
  distance = (float)atoi(strtok(NULL, "_"));

  Serial.print("Code: ");
  Serial.print(CurrentArduinoCode);
  Serial.print(", ID: ");
  Serial.print(sensorVariableId);
  Serial.print(", Distance: ");
  Serial.println(distance);

  client.add(sensorVariableId, distance);
  client.sendAll(false);

  
  Serial.println();
  for (int i = 0; i < sensorsCount; i++) {
    bool vibration = vibrations[i].getVibrationPool().vibration();
    Serial.print("Vibration is: ");

    if (vibration) {
      Serial.println("High");
      CurrentArduinoCode = POOL;
      break;
    }
    else {
      Serial.println("Low");
    }
  }

  //power On
  if (Alert.getPowerOn()){
    if(!Alert.getNotificationOn()){
      if (CurrentArduinoCode != NOTHING) {
        Alert.sendNotification(Alert.CodeToMessage(CurrentArduinoCode));
        Alert.setNotificationBtnOn();
        LastArduinoCode = CurrentArduinoCode;
      }
    } else 
    {
      if(CurrentArduinoCode == POOL){
        Alert.sendNotification(Alert.CodeToMessage(CurrentArduinoCode));
        LastArduinoCode = CurrentArduinoCode;
      }
        Alert.sendNotification(Alert.CodeToMessage(LastArduinoCode));
      }
    }
  }


BLYNK_WRITE(V0){
  Alert.setNotificationOn(param.asInt());
}

BLYNK_WRITE(V1){
  Alert.setPowerOn(param.asInt());
}