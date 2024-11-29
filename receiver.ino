#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);
int message;

int IN1 = 9; 
int IN2 = 3;
int IN3 = 6;
int IN4 = 5;  


void setup() {
  //this is to have the hc05's pair one as slave and the other as master
  BTSerial.begin(38400);
  Serial.begin(38400);      
  Serial.println("Slave:");   
    
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1,  LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,  LOW);
}

void  loop() {
  //these is recieving the signal and behaving according to it 
  if(BTSerial.available()>0)
  { 
    message=BTSerial.read();
    Serial.println(message);

    if(message == 48){
      backward();
      delay(2000);
    }
    if (message==49){
      forward();
      delay(2000);
    }
    if  (message == 50){
      stopCar();
      delay(2000);
    }
  }
}



void forward(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}

void stopCar(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}    

void backward(){
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}

