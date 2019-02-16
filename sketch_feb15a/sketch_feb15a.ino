/*HACK UCI 2019*/

/*setting up ultrasonic sensor*/
#include "SR04.h"
int TRIG_PIN = 12;
int ECHO_PIN = 11;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance; /*variable for recording distance*/

//set up buzzer
int buzzerPin = 13;

void setup() {
   Serial.begin(9600); /*starting serial monitor*/
   delay(1000);

}

void loop() {
   distance = sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
   delay(1000);
  

}
