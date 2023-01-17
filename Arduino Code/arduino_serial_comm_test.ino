# https://github.com/slawomirkorbas/robotics/blob/main/arduino_serial_comm_test/arduino_serial_comm_test.ino

void setup()
{
    Serial.begin(115200);

    while (!Serial) {
    ; // wait for serial port to connect.
  }
}

const char TERMINATOR = '|';

void loop()
{
    // waiting for command from Jetson...
    if (Serial.available() > 0)
    {
      //char messageBuffer[32];
      //int size = Serial.readBytesUntil('\n', messageBuffer, 32);
      String commandFromJetson = Serial.readStringUntil(TERMINATOR);
      
      // confirm 
      String ackMsg = "Hello Jetson! This is what I got from you: " + commandFromJetson; // String(messageBuffer);
      
      Serial.print(ackMsg);
      //Serial.flush();
    }
    delay(500);
}