int sensorpinright = A0; //Initialize input pin
int sensorpinleft = A1; //Initialize input pin
#include <Wire.h>
#include <Adafruit_MotorShield.h>
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
void setup() {
  // put your setup code here, to run once:
  pinMode(sensorpinright, INPUT);
  pinMode(sensorpinleft, INPUT);
  Serial.begin(9600);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  // Set the speed to start, from 0 (off) to 255 (max speed)
  
  myMotor1->setSpeed(150);
  myMotor2->setSpeed(150);
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(sensorpinright));Serial.println(analogRead(sensorpinleft));
  delay(100);
    uint8_t i;
  
  Serial.print("tick");

  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);  
    delay(10);
  }
  
  Serial.print("tock");

  myMotor1->run(BACKWARD);
  myMotor2->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);  
    delay(10);
  }

  Serial.print("tech");
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  delay(1000);
}
