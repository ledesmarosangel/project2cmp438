#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);
int message;

int IN1 = 9; 
int IN2 = 3;
int IN3 = 6;
int IN4 = 5;  


void setup() {
  BTSerial.begin(38400);
  Serial.begin(38400);      
 // Serial.println("Slave:");   
    
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
  //play with values
  if(BTSerial.available()>0)
  { 
    message=BTSerial.read();
    Serial.println(message);

    if(message == '0'){
      Serial.println("Reverse");
      reverse();
      delay(200);
    }
     if (message== '1'){
      Serial.println("Forward");
      forward();
      delay(200);
    }
     if  (message == '2'){
      Serial.println("Stop");
      stopCar();
      delay(200);
    }

     if  (message == '3'){
      Serial.println("Left");
      turnLeft();
      delay(200);
    }

    if  (message == '4'){
      Serial.println("Right");
      turnRight();
      delay(200);
    }

    

   
  }
}

void turnLeft(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
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

void reverse(){
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}

void turnRight(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}
