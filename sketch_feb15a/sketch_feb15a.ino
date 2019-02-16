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
int pitch = 0;
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int buzzDuration = 500;  // 500 miliseconds

//ARMS
//M1
int motorEN1 = 5;
int motorForward1 = 4;
int motorReverse1 = 2;
//M2
/*int motorEN2 = 3;
int motorForward2 = 1;
int motorReverse2 = 0;*/
//arm function declaration
int speed = 0;
void arms_forward(int);/*makes motor spin forward*/
void arms_reverse(int);/*makes motor spin backwards*/
void arms_off();/*turns motors off*/

//head
int headEN = 9;
int headForward = 7;
int headReverse = 8;
//head function declaration
int head_speed = 0;
void head_forward(int);
void head_reverse(int);
void head_off();

//p is for interation, contorlling pitch and servo speed
int p = 0;

//LEDs
int greenLED = 0;
int redLED = 1;
void attack_mode();
void neutral_mode();

/*main code*/
void setup() {
  //setting up serial monitor
  Serial.begin(9600); /*starting serial monitor*/
  delay(1000);
  //setting up pins
  pinMode (motorEN1, OUTPUT);
  pinMode(motorForward1, OUTPUT);
  pinMode(motorReverse1, OUTPUT);
  /*pinMode (motorEN2, OUTPUT);
  pinMode(motorForward2, OUTPUT);
  pinMode(motorReverse2, OUTPUT);*/
  pinMode (headEN, OUTPUT);
  pinMode(headForward, OUTPUT);
  pinMode(headReverse, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop() {
   distance = sr04.Distance();
   Serial.print(distance);
   Serial.println("cm");

   if (distance < 100) {
      p = distance/10;
      if (p < 1) {
        p = 1;
      }
      Serial.println(p);
      pitch = 3 * p;
      Serial.print("pitch ");
      Serial.println(pitch);
      speed = 255/p;
      Serial.print("arm speed ");
      Serial.println(speed);
      head_speed = 255/p;
      Serial.print("head speed ");
      Serial.println(head_speed);
      tone(buzzerPin, melody[pitch], buzzDuration);
      Serial.println("buzzer on");
      attack_mode();
      Serial.println("attack mode");
      if (distance % 2 == 0){
        arms_forward(speed);
        head_forward(head_speed);
      }
      else{
        arms_reverse(speed);
        head_reverse(head_speed);
      }
   } else {
     arms_off();
     neutral_mode();
     Serial.println("neutral mode");
   }
   delay(3000);
   arms_off();
   delay(500);
}


//motor functions
void arms_forward(int speed){
   Serial.println("arms forward");
   analogWrite(motorEN1, speed);
   digitalWrite(motorForward1, HIGH);
   digitalWrite(motorReverse1, LOW);
/*   analogWrite(motorEN2, speed);
   digitalWrite(motorForward2, HIGH);
   digitalWrite(motorReverse2, LOW);*/
   delay(100);
}

void arms_reverse(int speed){
  Serial.println("arms reverse");
  analogWrite(motorEN1, speed);
  digitalWrite(motorForward1, LOW);
  digitalWrite(motorReverse1, HIGH);
/*  analogWrite(motorEN2, speed);
  digitalWrite(motorForward2, LOW);
  digitalWrite(motorReverse2, HIGH);*/
  delay(100);
}

void arms_off(){
  Serial.println("arms off");
  speed = 0;
  analogWrite(motorEN1,speed);
  digitalWrite(motorForward1, LOW);
  digitalWrite(motorReverse1, LOW);
  /*analogWrite(motorEN2,speed);
  digitalWrite(motorForward2, LOW);
  digitalWrite(motorReverse2, LOW);*/
}

void head_forward(int speed){
   Serial.println("head forward");
   analogWrite(headEN, speed);
   digitalWrite(headForward, HIGH);
   digitalWrite(headReverse, LOW);
}

void head_reverse(int speed){
  Serial.println("head reverse");
  analogWrite(headEN, speed);
  digitalWrite(headForward, LOW);
  digitalWrite(headReverse, HIGH);
}

void head_off(){
  head_speed = 0;
  analogWrite(motorEN1,head_speed);
  digitalWrite(motorForward1, LOW);
  digitalWrite(motorReverse1, LOW);
}

void attack_mode(){
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
}
void neutral_mode(){
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
}
