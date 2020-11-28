#include <SoftwareSerial.h>

const int tx_pin = 2; // pin connected to RXD
const int rx_pin = 3; // pin connected to TXD

SoftwareSerial hc05_serial(rx_pin, tx_pin);

void setup() {
  // open PC serial
  Serial.begin(9600);
  Serial.print("Sketch: ");
  Serial.println(__FILE__);
  Serial.print("Uploaded: ");
  Serial.println(__DATE__);
  Serial.println(" ");

  // open HC-05 serial
  hc05_serial.begin(38400);
  Serial.println("Hc05Serial ready");
  Serial.println(" ");
}

void loop() {
  // forward incoming HC-05 data to PC
  while (hc05_serial.available())
    Serial.write(hc05_serial.read());

  // forward incoming PC data to HC-05
  while (Serial.available())
    hc05_serial.write(Serial.read());
}
