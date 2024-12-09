
//HC-05  
#include<SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);

//MPU6050
#include<Wire.h>
const int MPU_addr1 = 0x68;
float xa, ya, za, roll, pitch;

void setup(){
  //HC-05
  BTSerial.begin(38400);
  Serial.begin(38400);

  //MPU6050
  Wire.begin();                                      //begin the wire communication
  Wire.beginTransmission(MPU_addr1);                 //begin, send the slave address (in this case 68)
  Wire.write(0x6B);                                  //make the reset (place a 0 into the 6B register)
  Wire.write(0);
  Wire.endTransmission(true);                        //end the transmission
}



void loop(){

  mpuRead();
  printValues(); //- uncomment to this to callibrate the necessary values
  
  if( (roll >= -125 && roll <= -80) &&  (pitch>=-65 && pitch<=-15)){
    BTSerial.write('0');
    Serial.println("Reverse");
    delay(100);
    }

  else if((roll >= 60 && roll <= 140) &&  (pitch>=-80 && pitch<=-25)){
      BTSerial.write('1');
      Serial.println("Forward");
      delay(100);
    }
  else if ((roll >= -180 && roll <= -130) &&  (pitch>=-85 && pitch<=-68)){
      BTSerial.write('2');
      Serial.println("Stop");
      delay(100);
    }

  else if ((roll >= -100 && roll <= 25) &&  (pitch>=-100 && pitch<=-17)){
      BTSerial.write('3');
      Serial.println("Left");
      delay(100);
    }

  else if ((roll >= -190 && roll <= -135) &&  (pitch>=-35 && pitch<=18)){
      BTSerial.write('4');
      Serial.println("Right");
      delay(100);
  }


  else{
    BTSerial.write('2');
      Serial.println("Stop");
      delay(100);
  }

    



delay(500);
}
  

void mpuRead(){
  Wire.beginTransmission(MPU_addr1);
  Wire.write(0x3B);  //send starting register address, accelerometer high byte
  Wire.endTransmission(false); //restart for read
  Wire.requestFrom(MPU_addr1, 6); //get six bytes accelerometer data
  int t = Wire.read();
  xa = (t << 8) | Wire.read();
  t = Wire.read();
  ya = (t << 8) | Wire.read();
  t = Wire.read();
  za = (t << 8) | Wire.read();
// formula from https://wiki.dfrobot.com/How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing
  roll = atan2(ya , za) * 180.0 / PI;
  pitch = atan2(-xa , sqrt(ya * ya + za * za)) * 180.0 / PI; //account for roll already applied
}

void printValues(){
  Serial.print("roll = ");
  Serial.print(roll,2);
  Serial.print(", pitch = ");
  Serial.print(pitch,2);
  Serial.print(", xa = ");
  Serial.print(xa,2);
  Serial.print(", ya = ");
  Serial.println(ya, 2);
  delay(500);
}
