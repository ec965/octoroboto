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
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int buzzDuration = 500;  // 500 miliseconds

//set up M1 and M2 (SN754410..)
//M1
int motorEN1 = 5;
int motorForward1 = 4;
int motorReverse1 = 2;
//M2
int motorEN2 = 3;
int motorForward2 = 1;
int motorReverse2 = 0;
//set up M3(L293D)
int motorEN3 = 9;
int motorForward3 = 7;
int motorReverse3 = 8;

int speed = 0;
void forward(int);/*makes motor spin forward*/
void reverse(int);/*makes motor spin backwards*/
void off();/*turns motors off*/

/*main code*/
void setup() {
  //setting up serial monitor
  Serial.begin(9600); /*starting serial monitor*/
  delay(1000);
  //setting up pins
  pinMode(motorEN1, OUTPUT);
  pinMode(motorForward1, OUTPUT);
  pinMode(motorReverse1, OUTPUT);
  pinMode (motorEN2, OUTPUT);
  pinMode(motorForward2, OUTPUT);
  pinMode(motorReverse2, OUTPUT);
  pinMode (motorEN3, OUTPUT);
  pinMode(motorForward3, OUTPUT);
  pinMode(motorReverse3, OUTPUT); 

}

void loop() {
   distance = sr04.Distance();
   Serial.print(distance);
   Serial.println("cm");

   if (distance < 100) {
      tone(buzzerPin, melody[0], buzzDuration); 
      int p = (100 - (distance - 10)) / 100;
      int speed = 225 * p;
      forward(speed);     
   } else {
     off();
   }

   delay(1000);
}


//motor functions
void forward(int speed){
   Serial.println("forward");
   analogWrite(motorEN1, speed);
   digitalWrite(motorForward1, HIGH);
   digitalWrite(motorReverse1, LOW);
   analogWrite(motorEN2, speed);
   digitalWrite(motorForward2, HIGH);
   digitalWrite(motorReverse2, LOW);
}

void reverse(int speed){
  Serial.println("reverse");
  analogWrite(motorEN1, speed);
  digitalWrite(motorForward1, LOW);
  digitalWrite(motorReverse1, HIGH);
  analogWrite(motorEN2, speed);
  digitalWrite(motorForward2, LOW);
  digitalWrite(motorReverse2, HIGH);
}

void off(){
  Serial.println("off");
  speed = 0;
  analogWrite(motorEN1,speed);
  digitalWrite(motorForward1, LOW);
  digitalWrite(motorReverse1, LOW);
  analogWrite(motorEN2,speed);
  digitalWrite(motorForward2, LOW);
  digitalWrite(motorReverse2, LOW);
}
