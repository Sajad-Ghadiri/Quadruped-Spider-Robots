// ledPin refers to ESP32-CAM GPIO 4 (flashlight)
const int ledPin = 4;


void setup() {
  // put your setup code here, to run once:
   // initialize digital pin ledPin as an output
    pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  delay(2000);
  digitalWrite(ledPin, LOW);
  delay(2000);
}
