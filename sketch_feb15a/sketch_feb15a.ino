/*HACK UCI 2019*/

/*setting up ultrasonic sensor*/
#include "SR04.h"
int TRIG_PIN = 12;
int ECHO_PIN = 11;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance; /*variable for recording distance*/

//set up buzzer
int buzzerPin = 13;

//set up M1 and M2 (SN754410..)
//M1
int motorEN1 = 5;
int motorForward1 = 4;
int motorReverse1 = 2;
//M2
int motorEN2 = 3;
int motorForward2 = 1;
int motorReverse2 = 0;
int speed = 0;
void forward(int);/*makes motor spin forward*/
void reverse(int);/*makes motor spin backwards*/
void off(int);/*turns motors off*/
//set up M3(L293D)


/*main code*/
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


//M1 and M2 code
void forward(int speed){
   Serial.println("forward");
   speed = 255;
   analogWrite(motorEN1, speed);
   digitalWrite(motorForward1, HIGH);
   digitalWrite(motorReverse1, LOW);
   analogWrite(motorEN2, speed);
   digitalWrite(motorForward2, HIGH);
   digitalWrite(motorReverse2, LOW);
}

void reverse(int speed){
  Serial.println("reverse");
  speed = 255;
  analogWrite(motorEN1, speed);
  digitalWrite(motorForward1, LOW);
  digitalWrite(motorReverse1, HIGH);
  analogWrite(motorEN2, speed);
  digitalWrite(motorForward2, LOW);
  digitalWrite(motorReverse2, HIGH);
}

void off(int speed){
  Serial.println("off");
  speed = 0;
  analogWrite(motorEN1,speed);
  digitalWrite(motorForward1, LOW);
  digitalWrite(motorReverse1, LOW);
  analogWrite(motorEN2,speed);
  digitalWrite(motorForward2, LOW);
  digitalWrite(motorReverse2, LOW);
