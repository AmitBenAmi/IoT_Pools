#include <Alert.h>
#include <Vibration_pools.h>

char CurrentArduinoCode;
char LastArduinoCode;
Alert Alert;

void setup() {
 Serial.begin(9600);
 Alert.begin();
}

void loop() {
  Alert.start();
  CurrentArduinoCode = Alert.requestFromArduino(8,1);
  Serial.print("code:");
  Serial.println(CurrentArduinoCode);
  Serial.println(Alert.get_isNotificationOn());
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



