#include <SoftwareSerial.h>

const int tx_pin = 2; // pin connected to RXD
const int rx_pin = 3; // pin connected to TXD

SoftwareSerial hc05_serial(rx_pin, tx_pin);

bool blink = false;

void setup() {
  // open PC serial
  Serial.begin(9600);
  Serial.print("Sketch: ");
  Serial.println(__FILE__);
  Serial.print("Uploaded: ");
  Serial.println(__DATE__);
  Serial.println(" ");

  // open HC-05 serial
  hc05_serial.begin(9600);
  Serial.println("Hc05Serial ready");
  Serial.println(" ");

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (hc05_serial.available()) {
    int c = hc05_serial.read();
    Serial.write(c);
    switch (c) {
      case '1':
        blink = false;
        digitalWrite(LED_BUILTIN, HIGH);
        break;
      case '2':
        blink = false;
        digitalWrite(LED_BUILTIN, LOW);
        break;
      case '3':
        blink = true;
        break;
      default:
        break;
    }
  }
  if (blink) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(250);
}
