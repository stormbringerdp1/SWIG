char charValues[1];
byte byteValue;

int ledPin = 3;

void setup() {
  pinMode(ledPin, OUTPUT);   // sets the pin as output
  Serial.begin(9600);        // opens serial port, sets data rate to 9600 bps
}

void loop() {
// send data only when you receive data:
  if(Serial.available() > 0) {
    // read one incoming char:
    if(Serial.readBytes(charValues, 1) > 0) {
      byteValue = byte(charValues[0]);
//      if(0 <= charValues[0] && byteValues[0] <= 255) {
      analogWrite(ledPin, byteValue);
//      }
    }
  }
}
