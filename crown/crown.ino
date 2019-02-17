/*HACK UCI 2019*/

/*setting up ultrasonic sensor*/
#include "SR04.h"
#include "pitches.h"

#define TRIGB_PIN 13
#define ECHOB_PIN 11

#define TRIGR_PIN 12
#define ECHOR_PIN 10

#define TRIGL_PIN 8
#define ECHOL_PIN 9

SR04 sb = SR04(ECHOB_PIN,TRIGB_PIN);
SR04 sr = SR04(ECHOR_PIN,TRIGR_PIN);
SR04 sl = SR04(ECHOL_PIN,TRIGL_PIN);

long distanceB; /*variable for recording distance*/
long distanceR;
long distanceL;

//set up buzzer
int buzzerPin = 6;
int pitch = 0;
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int buzzDuration = 500;  // 500 miliseconds

//p is for interation, contorlling pitch and servo speed
int p = 0;

/*main code*/
void setup() {
  //setting up serial monitor
  Serial.begin(9600); /*starting serial monitor*/
  delay(1000);
}

void loop() {
   distanceB = sb.Distance();
   distanceR = sr.Distance();
   distanceL = sl.Distance();

   Serial.print("B:");
   Serial.print(distanceB);
   Serial.println("cm");

   Serial.print("R:");
   Serial.print(distanceR);
   Serial.println("cm");

   Serial.print("L:");
   Serial.print(distanceL);
   Serial.println("cm");

   if (distanceB < 100) {
      p = distanceB/10;
      if (p < 1) {
        p = 1;
      }
      Serial.println(p);
      pitch = 3 * p;
      Serial.print("pitch ");
      Serial.println(pitch);
      tone(buzzerPin, melody[pitch], buzzDuration);
      Serial.println("buzzer on");
   }

    if (distanceR < 100) {
      p = distanceR/10;
      if (p < 1) {
        p = 1;
      }
      Serial.println(p);
      pitch = 3 * p;
      Serial.print("pitch ");
      Serial.println(pitch);
      tone(buzzerPin, melody[pitch], buzzDuration);
      Serial.println("buzzer on");
   }

   if (distanceL < 100) {
      p = distanceL/10;
      if (p < 1) {
        p = 1;
      }
      Serial.println(p);
      pitch = 3 * p;
      Serial.print("pitch ");
      Serial.println(pitch);
      tone(buzzerPin, melody[pitch], buzzDuration);
      Serial.println("buzzer on");
   }

   delay(1000);
}
