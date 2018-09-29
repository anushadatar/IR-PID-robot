// Tommy Weir and Anusha Datar
// PoE Lab 3: Line-Following Robot

// Include headers for motor shield and connections.
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Left motor pin on motor shield.
int leftMotorPin = 3;
// Right motor pin on motor shield.
int rightMotorPin = 4;
// Left IR sensor pin.
int leftSensorPin = A0;
// Right IR sensor pin.
int rightSensorPin = A1; 
// Baudrate of serial. Important to match this for real-time testing.
int baudrate = 9600;

// Create the motor shield object with the default I2C address.
// Configure motor as specified in program.
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(leftMotorPin);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(rightMotorPin);

int verify_IR_sensor(int sensorPin, int threshold, int samplesPerMeasurement) {
/* Utility method to measure IR sensor data on some pin for some number of 
 * samples to check if the value is above some user-specified threshold.
 * 
 * sensorPin = INT The pin of the sensor to read data on - should be 
 * an analog input pin ideally.
 * threshold = INT The pin of the se
 * samplesPerMeasurement = INT the number of samples to read per measurement.
 * Increasing the number of samples will decrease the amount of jerkiness.
 * 
 * Returns TRUE if the sensor value does NOT exceed the threshold and FALSE
 * if the value does exceed the threshold.
 * 
 * Kept all values as ints to maximize for efficiency here because of the high
 * volume of calls made on this function.
 */
  int sum = 0;
  for (int numberOfReads = 0; numberOfReads < samplesPerMeasurement; numberOfReads++) {
    sum += analogRead(sensorPin);
    delay(5);  
  }
  int average = sum/sensorPin;
  if (average < threshold) {
    return true;
  }
  return average;
}

void set_speed_and_direction(Adafruit_DCMotor *motor, int inputSpeed) {
  /* Set wheel speed and direction for a given motor.
   *
   * motor = Pointer to Adafruit_DCMotor to change speed of.
   * inputSpeed = INT speed to set the motor to run at.
   */
  // If the direction is to stop.
  if (inputSpeed == 0) {
    motor->run(RELEASE);
    return;
  }
  int defaultDirection;
  // If the direction is backwards.
  if (inputSpeed < 0) {
    inputSpeed = -inputSpeed;
    defaultDirection = BACKWARD;
  }
  // If the direction is forwards.
  else {
    defaultDirection = FORWARD; 
  }
  // If the speed is too high.
  if (inputSpeed > 255) {
    inputSpeed = 255;
  }
  // Run the motors.
  motor->setSpeed(inputSpeed); 
  motor->run(defaultDirection);
}

void setup() {
  pinMode(rightSensorPin, INPUT);
  pinMode(leftSensorPin, INPUT);
  Serial.begin(baudrate);
  AFMS.begin();
}

void loop() {
// TODO : Add this method such that the car travels in a reasonable way
// Probably define some variables up top like 
// - default speed
// - default delta (it won't quite be proportional, but we can tune this
// delta value to create some meaning
// - default time in between samples

// Once we do that, we can create a serial interface that will communicate 
// with the car in pseudo real time. 
  // Over some time of delay
    // Read each of the sensors
    // If left sensor is over threshold, subtract some delta 
    // from the left wheel speed and add some delta to the right
    // wheel speed.

    // If right sensor is over threshold, subtract some delta to
    // the right wheel speed and some delta to the left wheel speed
}
