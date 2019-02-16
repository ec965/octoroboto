//M1
int motorEN1 = 5;
int motorForward1 = 4;
int motorReverse1 = 2;
//M2
int motorEN2 = 3;
int motorForward2 = 1;
int motorReverse2 = 0;
int speed = 0;
void forward();
void reverse();
void off();
//LED
//int ledPin = 13;
  

void setup() {
  pinMode (motorEN1, OUTPUT);
  pinMode(motorForward1, OUTPUT);
  pinMode(motorReverse1, OUTPUT);
  pinMode (motorEN2, OUTPUT);
  pinMode(motorForward2, OUTPUT);
  pinMode(motorReverse2, OUTPUT);
  //LED
  //pinMode(ledPin,OUTPUT);
}

void loop() {
  //LED
  //digitalWrite(ledPin,HIGH);
  forward();
  delay(2000);
  //digitalWrite(ledPin,LOW);
  off();
  delay(1000);
  reverse();
  delay(2000);
  off();
  delay(1000);
}

void forward(){
   Serial.println("forward");
   speed = 255;
   analogWrite(motorEN1, speed);
   digitalWrite(motorForward1, HIGH);
   digitalWrite(motorReverse1, LOW);
   analogWrite(motorEN2, speed);
   digitalWrite(motorForward2, HIGH);
   digitalWrite(motorReverse2, LOW);
}

void reverse(){
  Serial.println("reverse");
  speed = 255;
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
