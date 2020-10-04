#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps_V6_12.h"
#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// the MPU
MPU6050 mpu;

// DMP buffer
uint8_t fifoBuffer[64];

// the OLED display
Adafruit_SSD1306 display(4);

// constants
const float rad_to_deg = 180 / M_PI;

// global variables
float min_roll = 0;
float max_roll = 0;

void setup()
{
  Wire.begin();
  Wire.setClock(400000);

  Serial.begin(115200);

  // initialize the MPU
  Serial.println(F("Initializing MPU..."));
  mpu.initialize();

  Serial.println(F("Initializing DMP..."));
  uint8_t mpuStatus = mpu.dmpInitialize();

  if (mpuStatus == 0) {
    Serial.println(F("Calibrating the MPU..."));
    mpu.setXAccelOffset(-2609);
    mpu.setYAccelOffset(332);
    mpu.setZAccelOffset(1822);

    mpu.setXGyroOffset(51);
    mpu.setYGyroOffset(-31);
    mpu.setZGyroOffset(35);

    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);

    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);
  } else {
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(mpuStatus);
    Serial.println(F(")"));
    while (true)
      delay(100);
  }

  // initialize the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // hide the Adafruit welcome screen
  display.clearDisplay();
  display.display();
}

void loop()
{
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
    Quaternion q;
    mpu.dmpGetQuaternion(&q, fifoBuffer);

    VectorFloat gravity;
    mpu.dmpGetGravity(&gravity, &q);

    float ypr[3];
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    const float roll = ypr[2] * rad_to_deg;
    min_roll = min(roll, min_roll);
    max_roll = max(roll, max_roll);

    Serial.print(ypr[0] * rad_to_deg, 1);
    Serial.print(" ");
    Serial.print(ypr[1] * rad_to_deg, 1);
    Serial.print(" ");
    Serial.println(roll, 1);

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
  
    display.setTextSize(2);
    display.setCursor(0, 50);
    display.print(fabs(min_roll), 1);
  
    display.setCursor(80, 50);
    display.print(fabs(max_roll), 1);
  
    display.setTextSize(3);
    display.setCursor(0, 10);
  
    if (roll < 0)
      display.print('<');
    else if (roll > 0)
      display.print('>');
    else
      display.print(' ');
  
    float abs_roll = fabs(roll);
    if (abs_roll < 10)
      display.setCursor(37, 10);
    else
      display.setCursor(28, 10);
    display.print(abs_roll, 1);
   
    display.display();
  }
}
