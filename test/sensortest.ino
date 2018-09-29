int tape = 1; // Making variable for tape
int sensorpin = A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(sensorpin, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(sensorpin));
  delay(100);
}
