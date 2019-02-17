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

int farthest_distance = 100; //farthest distance before stuff starts happening

//set up buzzer
int buzzerPin = 6;
int pitch = 0;
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
long buzzDuration = 0;  // initialize

//LED pins
int blue_back = 4;
int yellow_right = 3;
int red_left = 2;

//p is for interation, contorlling pitch and servo speed
int p = 0;

//finding the lowest number of three numbers
int lowestnum(int, int, int);
/*main code*/
void setup() {
  //setting up serial monitor
  Serial.begin(9600); /*starting serial monitor*/
  delay(1000);
  pinMode(blue_back, OUTPUT);
  pinMode(yellow_right, OUTPUT);
  pinMode(red_left, OUTPUT);
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
   
   if (distanceB < farthest_distance || distanceR < farthest_distance || distanceL < farthest_distance){
     if (distanceB < farthest_distance){ //to active back/front LED
      digitalWrite(blue_back, HIGH);
     }
     if (distanceR < farthest_distance){ //active right LED
      digitalWrite(yellow_right, HIGH);
     }
     if (distanceL < farthest_distance){ //activate left LED
      digitalWrite(red_left, HIGH);
     }
    p = 2*lowestnum(distanceB, distanceR, distanceL)/5; //creates a varible to adjust bitch and buzzing duration
    if (p<1){
      p = 1;
    }
    Serial.print("value p: ");
    Serial.println(p);
    pitch = 4*p;
    buzzDuration = p*100;
    Serial.print("buzz duration: ");
    Serial.println(buzzDuration);
    Serial.print("pitch: ");
    Serial.println(pitch);
    tone(buzzerPin, melody[pitch], buzzDuration);
    Serial.println("buzzer on");
    digitalWrite(blue_back, LOW);
    digitalWrite(yellow_right, LOW);
    digitalWrite(red_left, LOW);
   } 
   else{
      digitalWrite(blue_back, LOW);
      digitalWrite(yellow_right, LOW);
      digitalWrite(red_left, LOW);
   }
   delay(200);
}

int lowestnum(int A, int B, int C){
  int smallest = A;
  if (smallest > B){
    smallest = B;
  }
  if (smallest > C){
    smallest = C;
  }
  return smallest;
}
