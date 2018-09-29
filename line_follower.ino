// Tommy Weir and Anusha Datar
// PoE Lab 3: Line-Following Robot

// TODO :
  // Manual tuning + testing 
  // Potentially a more sophisticated controller?
  // Serial interface to communicate with robot and update parameters in pseudo RT
  // DEBUG prints + plot of sensor values + suggested motor speeds.

// Include headers for motor shield and connections.
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Pin definitions and associated constants.
int leftMotorPin = 3;
int rightMotorPin = 4;
int leftSensorPin = A0;
int rightSensorPin = A1; 
// Baudrate of serial. Important to match this on all programs.
int baudrate = 9600;

// TODO : These constants need to be determined and tuned.
// Initial constants for motion controller.
// The initial speed of each motor.
int initialSpeed = 40; 
// The initial speed by which to turn the motors if the tape is recognized.
// NOTE: This slows down the corresponding motor and speeds up the opposite motor 
// at the same time, so the net delta is 2 x initial_speed_delta/ 
int initialSpeedDelta = 30;
// The initial threshold for the IR sensor - below this value is black tape, above
// this value is the tile floor.
int initialThreshold = 970;
// The samples per measurement to start with for the IR sensor. 
int initialSamplesPerMeasurement = 5;

// Create the motor shield object with the default I2C address.
// Configure motor as specified in program.
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(leftMotorPin);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(rightMotorPin);


////// Helper Methods.
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
 * Returns TRUE if the sensor value is lower than the threshold and FALSE
 * if the value does exceed the threshold.
 * 
 * In the case of the line following robot, TRUE means that the value is BELOW the
 * threshold and the robot is ON the black tape, while FALSE means that the value
 * is ABOVE the threshold and the robot is OFF the black tape.
 * 
 * Kept all values as ints to maximize for efficiency here because of the high
 * volume of calls made on this function.
 */
  int sum = 0;
  for (int numberOfReads = 0; numberOfReads < samplesPerMeasurement; numberOfReads++) {
    sum += analogRead(sensorPin);
    delay(2);  
  }
  int average = sum/sensorPin;
  if (average < threshold) {
    return true;
  }
  else {
    return false;
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
  // Set the initial constants. It can be tuned over serial as well, but we should have a starting point before setup.
  int speedDelta = initialSpeedDelta;
  int threshold = initialThreshold;
  int samples = initialSamplesPerMeasurement;
  bool leftSensorValue = verify_IR_sensor(leftSensorPin, threshold, initialSamplesPerMeasurement);
  // If the left sensor ia off the tape, we want to speed up the left motor to get back on track.
  if (!leftSensorValue) {
    // TODO Figure out passing this pointer correctly.
    set_speed_and_direction(leftMotor, speedDelta);
    set_speed_and_direction(rightMotor, -speedDelta);
  }
  bool rightSensorValue = verify_IR_sensor(leftSensorPin, threshold, initialSamplesPerMeasurement);
  if (!rightSensorValue) {
    set_speed_and_direction(rightMotor, speedDelta);
    set_speed_and_direction(leftMotor, -speedDelta);
  }
}
