// Serial interface test code.

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Set the initial constants. It can be tuned over serial as well, but we should have a starting point before setup.
  int speedDelta = 0;
  int threshold = 0;
  int samples = 0;
  // Check the serial interface in case any of these constants need to be changed. 
  // Command formatting should be as such: 
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
   else {
    Serial.println("Serial command not found.");
   }
   // Debug printing.
   Serial.print("speed delta : ");
   Serial.print(speedDelta);
   Serial.print("\n");
   Serial.print("threshold : ");
   Serial.print(threshold);
   Serial.print("\n");
   Serial.print("samples : ");
   Serial.print(samples);
   Serial.print("\n");   
   delay(1000);
}
