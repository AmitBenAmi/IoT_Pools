#include <Alert.h>
#include <VibrationUbidots.h>

// Ubidots vibration IDs
char* d6VibrationUbidots = "5b5337c2c03f9758774e5039";
char* d7VibrationUbidots = "5b5337c8c03f9758774e503c";

VibrationUbidots vibrations[] = {
  { VibrationUbidots(d6VibrationUbidots, VibrationPools(D6)) },
  { VibrationUbidots(d7VibrationUbidots, VibrationPools(D7)) }
};

int sensorsCount = 0;

char CurrentArduinoCode;
char LastArduinoCode;
Alert Alert;

void setup() {
  Serial.begin(9600);
  Alert.begin();

  sensorsCount = sizeof(vibrations)/sizeof(vibrations[0]);

  for (int i = 0; i < sensorsCount; i++) {
    vibrations[i].getVibrationPool().begin();
  }
}

void loop() {
  Alert.start();
  CurrentArduinoCode = Alert.requestFromArduino(8,1);
  
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

  Serial.print("code:");
  Serial.println(CurrentArduinoCode);

  //power On
  if (Alert.get_isPowerOn()){
    //Notification off 
    if(!Alert.get_isNotificationOn()){
      if (CurrentArduinoCode != NOTHING) {
        Alert.sendNotification(Alert.CodeToMessage(CurrentArduinoCode));
        Alert.set_NotificationBtnOn();
        LastArduinoCode = CurrentArduinoCode;
        Serial.print("last:");
        Serial.println(LastArduinoCode);
      }
    } else //notification on (allready send a message)
    {
      Serial.println("notification ON");
      // if new message is pool alert, chang the message. if not, continue send the last message
      if(CurrentArduinoCode == POOL){
        Serial.println(Alert.CodeToMessage(CurrentArduinoCode));
        Alert.sendNotification(Alert.CodeToMessage(CurrentArduinoCode));
      } else {
        Serial.print("last:");
        Serial.println(LastArduinoCode);
        Serial.println(Alert.CodeToMessage(LastArduinoCode));
        Alert.sendNotification(Alert.CodeToMessage(LastArduinoCode));
      }
    }
  }
}


BLYNK_WRITE(V0){
  Serial.println("hello");
  Alert.set_isNotificationOn(param.asInt());
}

BLYNK_WRITE(V1){
  Alert.set_isPowerOn(param.asInt());
}