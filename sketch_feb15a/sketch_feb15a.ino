/*HACK UCI 2019*/

/*setting up ultrasonic sensor*/
#include "SR04.h"
#include "pitches.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

long distance; /*variable for recording distance*/

//set up buzzer
int buzzerPin = 13;
double p = 0;
int pitch = 0;
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int buzzDuration = 500;  // 500 miliseconds

//set up M1 and M2 (SN754410..)
//M1
int motorEN = 5;
int motorForward = 4;
int motorReverse = 2;

int speed = 0;
void forward();/*makes motor spin forward*/
void reverse();/*makes motor spin backwards*/
void off();/*turns motors off*/

/*main code*/
void setup() {
  //setting up serial monitor
  Serial.begin(9600); /*starting serial monitor*/
  delay(1000);
  //setting up pins
  pinMode(motorEN, OUTPUT);
  pinMode(motorForward, OUTPUT);
  pinMode(motorReverse, OUTPUT);
}

void loop() {
   distance = sr04.Distance();
   Serial.print(distance);
   Serial.println("cm");

   if (distance < 100) {
      p = (100 - (distance - 10)) / 100;
      if (p > 1) {
        p = 1;
      }
      pitch = 7 * p;
      forward();   
      tone(buzzerPin, melody[pitch], buzzDuration); 
   } else {
     off();
   }

   delay(1000);
}


//motor functions
void forward(){
   speed = 255;
   Serial.println("forward");
   analogWrite(motorEN, speed);
   digitalWrite(motorForward, HIGH);
   digitalWrite(motorReverse, LOW);
}

void reverse(){
  speed = 255;
  Serial.println("reverse");
  analogWrite(motorEN, speed);
  digitalWrite(motorForward, LOW);
  digitalWrite(motorReverse, HIGH);
}

void off(){
  Serial.println("off");
  speed = 0;
  analogWrite(motorEN,speed);
  digitalWrite(motorForward, LOW);
  digitalWrite(motorReverse, LOW);
}
