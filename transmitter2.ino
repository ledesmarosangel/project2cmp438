
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

//we got this from a tutorial
  //MPU6050
  Wire.begin();                                      //begin the wire communication
  Wire.beginTransmission(MPU_addr1);                 //begin, send the slave address (in this case 68)
  Wire.write(0x6B);                                  //make the reset (place a 0 into the 6B register)
  Wire.write(0);
  Wire.endTransmission(true);                        //end the transmission
  
}



void loop(){

  mpuRead();
  printValues(); 
  
  if(roll<-2 || pitch>6){
    BTSerial.write('0');
    Serial.println("backward");
    delay(100);
    }

  else if(roll>5 || pitch <-2){
      BTSerial.write('1');
      Serial.println("forward");
      delay(100)0;
    }

else {
      BTSerial.write('2');
      Serial.println("stop");
      delay(1000);
    }

delay(500);
}
  

//we got the following from a tutorial -rosangel & hamza

//
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
  //end of tutorial code
}