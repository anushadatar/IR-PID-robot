// Tommy Weir and Anusha Datar
// PoE Lab 3: Line-Following Robot

/*
 * This file contains all of the arduino code associated with Principles of Engineering lab
 * 3 as a consolidated unit. All files used to test electronics and mechanical assemblies can
 * be found in the tests/ directory in this repository.
 */

// TODO :
  // Manual tuning + testing 
  // Potentially a more sophisticated controller?
  // DEBUG prints + plot of sensor values + suggested motor speeds for final report

// Include headers for motor shield and connections.
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Pin definitions and associated constants.
int leftMotorPin = 1;
int rightMotorPin = 2;
int leftSensorPin = A0;
int rightSensorPin = A1; 
// Baudrate of serial. Important to match this on all programs.
int baudrate = 9600;

// Initial constants for motion controller.
// The initial speed of each motor.
int initialSpeed = 30; 
// The initial speed by which to turn the motors if the tape is recognized.
// NOTE: This slows down the corresponding motor and speeds up the opposite motor 
// at the same time, so the net delta is 2 x initial_speed_delta/ 
int initialSpeedDelta = 15;
// The initial threshold for the IR sensor - ABOVE this value is black tape, BELOW
// this value is the tile floor.
int initialThreshold = 950;
// The samples per measurement to start with for the IR sensor. 
int initialSamplesPerMeasurement = 5;

// Create the motor shield object with the default I2C address.
// Configure motor as specified in program.
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(leftMotorPin);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(rightMotorPin);

//// Helper Methods.
int verify_IR_sensor(int sensorPin, int threshold, int samplesPerMeasurement) {
/* Utility method to measure IR sensor data on some pin for some number of 
 * samples to check if the value is above some user-specified threshold.
 * 
 * sensorPin : INT The pin of the sensor to read data on - should be 
 *             an analog input pin ideally.
 * threshold : INT The value BELOW which the value is black tape and ABOVE which
 *             the value is tile floor.
 * samplesPerMeasurement : INT the number of samples to read per measurement.
 *                         Increasing the number of samples will decrease the 
 *                         amount of jerkiness but also increase the amount of error.
 * 
 * Returns : FALSE if the sensor value is HIGHER than the threshold and TRUE
 *           if the value is LOWER than the threshold.
 * 
 * In the case of the line following robot, FALSE means that the value is ABOVE the
 * threshold and the robot is ON the black tape, while TRUE means that the value
 * is BELOW the threshold and the robot is OFF the black tape.
 * 
 * Kept all values as ints to maximize for efficiency here because of the high
 * volume of calls made on this function.
 */
  int sum = 0;
  for (int numberOfReads = 0; numberOfReads < samplesPerMeasurement; numberOfReads++) {
    sum += analogRead(sensorPin);
    delay(10);  
  }
  // Grab average based on samples per measurement.
  int average = sum/samplesPerMeasurement;
  if (average > threshold) {
    return false;
  }
  else {
    return true;
  }
}
void set_speed_and_direction(Adafruit_DCMotor *motor, int inputSpeed) {
  /* Set wheel speed and direction for a given motor.
   *  
   * motor = Pointer to Adafruit_DCMotor to change speed of.
   * inputSpeed = INT speed to set the motor to run at.
   * 
   * Runs sanity and direction check and then assigns value to motor.
   */
  int defaultDirection;
   
  // If the direction is to stop.
  if (inputSpeed == 0) {
    motor->run(RELEASE);
    return;
  }
  
  // If the direction is backwards.
  if (inputSpeed < 0) {
    inputSpeed = -inputSpeed;
    defaultDirection = BACKWARD;
  }
  
  // If the direction is forwards.
  else {
    defaultDirection = FORWARD; 
  }
  
  // If the speed is too high, cap it at 255.
  if (inputSpeed > 255) {
    inputSpeed = 255;
  }

  // Run the motors as directed.
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
  // Set the initial constants. It can be tuned over serial as well, but we should have a starting point before setup.
  int speedDelta = initialSpeedDelta;
  int threshold = initialThreshold;
  int samples = initialSamplesPerMeasurement;

  // Check the serial interface in case any of these constants need to be changed. 
  // Command formatting should be as such (note place value limitations): 
  // - To set speed delta : "D : ###"
  // - To set threshold : "T : ####"
  // - To set sample rate : "S : ###"
  if(Serial.available()){
        String command;
        command = Serial.readStringUntil("\n");
        Serial.println(command);
        if (command[0] == ('D')) {
          speedDelta = (command.substring(4,7)).toInt();
          Serial.print("Delta updated to : ");
          Serial.print(speedDelta);
          Serial.print('\n');
        }
        if (command[0] == 'T') {
          threshold = (command.substring(4, 8)).toInt();
          Serial.print("Threshold updated to : ");
          Serial.print(threshold);
          Serial.print('\n');
        }
        if (command[0] == 'S') {
          samples = (command.substring(4, 7)).toInt();
          Serial.print("Sample rate updated to : ");
          Serial.print(samples);
          Serial.print('\n');
        }
   }
  bool leftSensorValue = verify_IR_sensor(leftSensorPin, threshold, initialSamplesPerMeasurement);
  bool rightSensorValue = verify_IR_sensor(rightSensorPin, threshold, initialSamplesPerMeasurement);
  // If the left sensor is on the tape, we want to speed up the left motor to get back on track.
  if (!leftSensorValue) {
    // TODO Figure out passing this pointer correctly.
    set_speed_and_direction(leftMotor, -speedDelta);
    set_speed_and_direction(rightMotor, speedDelta);
    Serial.print("Left above threshold. Speed delta: ");
    Serial.print(speedDelta);
    Serial.print("\n");
  }
  if (!rightSensorValue) {
    set_speed_and_direction(rightMotor, -speedDelta);
    set_speed_and_direction(leftMotor, speedDelta);
    Serial.print("Right above threshold. Speed delta: ");
    Serial.print(speedDelta);
    Serial.print("\n");
  }
  if (leftSensorValue && rightSensorValue) {
    set_speed_and_direction(rightMotor, initialSpeed);
    set_speed_and_direction(leftMotor, initialSpeed);
    Serial.print("Going forwards. \n");
  }
  delay(20);
}
