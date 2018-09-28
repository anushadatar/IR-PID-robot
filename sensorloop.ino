int sensorpinright = A0 //Initialize input pin
int sensorpinleft = A1 //Initialize input pin
#include <Wire.h>
#include <Adafruit_MotorShield.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorpinright, INPUT);
  pinMode(sensorpinleft, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(sensorpin));
  delay(100);
}
