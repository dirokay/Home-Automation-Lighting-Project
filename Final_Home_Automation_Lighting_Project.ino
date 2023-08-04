#include<Stepper.h>
//My relay is in the low Level trigger mode

//gobal variables declaration
const int LDR = 3; //digital input pin ldr
const int PIR = 2; //digital innput pin pir
const int micPin = 12; //digital input pin microphone
const int stepsPerRevolution = 2048; //stepper motor
const int relay = 8; //relay digital input pin
Stepper stepper(stepsPerRevolution, 4, 6, 5, 7);

// function declaration
int readLDR(); //read LDR value whether a high or a low
int readMic(); //read mic state
int readMotion(); //reads motion state

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (LDR, INPUT);
  pinMode (PIR, INPUT);
  pinMode(micPin, INPUT);
  pinMode(relay, OUTPUT);
  //digitalWrite(relay, LOW) -  activates the relay
  //digitalWrite(relay, HIGH) -  deactivates the relay
  digitalWrite(relay, HIGH); //relay starts being deactivated
  //delay(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int LDRvalue = digitalRead(LDR); //defining ldr function
 Serial.println(LDRvalue);
//  //PIR
 int motionState = digitalRead(PIR);
 Serial.println(motionState);
 delay(500);
//  //MICROPHONE
  int micState = digitalRead(micPin);
  Serial.println(micState);
 delay(500);
 readLDR();
}

int readLDR() {
  int LDRvalue = digitalRead(LDR);
  if (LDRvalue == 1) { //DARK
    Serial.println("Low light intensity, Lights ON");
    digitalWrite(relay, LOW); //ON
    stepper.setSpeed(5);
    Serial.println("curtains close"); //step 1 revolution in clockwise direction
    stepper.step(stepsPerRevolution); //makes it rotate cw direction
//micState
readMic();
delay(2000);
//motion
readMotion();
  }
  else{
    Serial.println("High light intensity, lights OFF");
    digitalWrite(relay, HIGH); //Lights OFF
    stepper.setSpeed(5);
    Serial.println("curtains open"); //step 1 revolution in counter-clockwise direction
    stepper.step(-stepsPerRevolution); //makes it rotate CCW direction
  }
}
  //defining readMic 
  int readMic(){
     int micState = digitalRead(micPin);
     if (micState == 1) { //while lights ON
      Serial.println("That's  definitely a clap,lights OFF");
      digitalWrite(relay, HIGH); //switches lights OFF
      delay(5000);
  }
   }

  //defining readMotion
int readMotion(){
    int motionState = digitalRead(PIR);
      if (motionState == 1 ) { //while lights are OFF
        Serial.println("Motion detected, lights back ON");
        digitalWrite(relay, LOW); //ON
        delay(5000);
      }
   }
  
