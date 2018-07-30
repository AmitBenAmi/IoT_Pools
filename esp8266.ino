#include <Alert.h>
#include <VibrationUbidots.h>
#include <UbidotsMicroESP8266.h>

VibrationUbidots vibrations[] = {
  { VibrationUbidots(D6_VIBRATION_UBIDOTS_VARIABLE_ID, VibrationPools(D6)) },
  { VibrationUbidots(D7_VIBRATION_UBIDOTS_VARIABLE_ID, VibrationPools(D7)) }
};

int sensorsCount = 0;

char dataFromArduino[ARDUINO_ESP8266_COMMUNICATION_REQUEST_LENGTH];
char CurrentArduinoCode = NOTHING;
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
  Alert.requestFromArduino(ARDUINO_ESP8266_COMMUNICATION_ID, ARDUINO_ESP8266_COMMUNICATION_REQUEST_LENGTH).toCharArray(dataFromArduino, ARDUINO_ESP8266_COMMUNICATION_REQUEST_LENGTH);

  Serial.println(dataFromArduino);

  if (strlen(dataFromArduino) == 0) {
    Serial.println("No data from arduino");
  } else {
    char code = strtok(dataFromArduino, "_")[0];
    char * sensorVariableId;
  
    for (int i = 0; i < 4; i++) {
  
      if (CurrentArduinoCode == NOTHING) {
        CurrentArduinoCode = code;
      }
      
      sensorVariableId = strtok(NULL, "_");
      float distance = (float)atoi(strtok(NULL, "_"));
  
      Serial.print("Code: ");
      Serial.print(code);
      Serial.print(", ID: ");
      Serial.print(sensorVariableId);
      Serial.print(", Distance: ");
      Serial.println(distance);
  
      client.add(sensorVariableId, distance);
  
      code = strtok(NULL, "_")[0];
    }
  
    Serial.println("Read all arduino data");
    client.sendAll(false);
  
    for (int i = 0; i < sensorsCount; i++) {
      bool vibration = vibrations[i].getVibrationPool().vibration();
      Serial.print("Vibration is: ");
  
      if (vibration) {
        Serial.println("High");
        CurrentArduinoCode = POOL;
      }
      else {
        Serial.println("Low");
      }
  
      client.add(vibrations[i].getID(), (float)vibration);
    }
  
    client.sendAll(false);

    Serial.print("CurrentArduinoCode: ");
    Serial.println(CurrentArduinoCode);
  
    //power On
    if (Alert.getPowerOn()){
      if(!Alert.getNotificationOn()){
        if (CurrentArduinoCode != NOTHING) {
          Alert.sendNotification(Alert.CodeToMessage(CurrentArduinoCode));
          Alert.setNotificationBtnOn();
          LastArduinoCode = CurrentArduinoCode;
        }
      } else {
        if(CurrentArduinoCode == POOL){
          LastArduinoCode = CurrentArduinoCode;
        }

        if (LastArduinoCode != NOTHING) {
          Alert.sendNotification(Alert.CodeToMessage(LastArduinoCode)); 
        }
      }
    } 
  }
}

BLYNK_WRITE(V0){
  Alert.setNotificationOn(param.asInt());
  CurrentArduinoCode = NOTHING;
  LastArduinoCode = CurrentArduinoCode;
}

BLYNK_WRITE(V1){
  bool value = param.asInt();
  Alert.setPowerOn(value);
  CurrentArduinoCode = NOTHING;
  LastArduinoCode = CurrentArduinoCode;

  if (!value) {
    Alert.setNotificationBtnOff();
  }
}