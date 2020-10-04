#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>

// enable the serial (use for debug only, it interferes with the display)
// #define USE_SERIAL 1

// the MPU used
Adafruit_MPU6050 mpu;

const int8_t MPU_I2C_ADDR = 0x68; // address of the MPU-6050 device
const int8_t PWR_MGMT_1   = 0x6B; // power management 1 register address
const int8_t XA_OFFS_USRH = 0x06; // accelerometer offset cancellation
const int8_t XG_OFFS_USRH = 0x13; // gyro offset cancellation

// MPU6050 calibration data (YMMV)
const int16_t offset_acel_x = -2609;
const int16_t offset_acel_y =   332;
const int16_t offset_acel_z =  1822;
const int16_t offset_gyro_x =    51;
const int16_t offset_gyro_y =   -31;
const int16_t offset_gyro_z =    35;

// the OLED display used
Adafruit_SSD1306 display(4);

// global variables
float min_roll = 0;
float max_roll = 0;

void setup(void) {
#ifdef USE_SERIAL
  Serial.begin(9600);
#endif

  // initialize the mpu
  if (!mpu.begin()) {
#ifdef USE_SERIAL
    Serial.println("Failed to find MPU6050 chip");
#endif
    while (1) {
      delay(10);
    }
  }
#ifdef USE_SERIAL
  Serial.println("MPU6050 Found!");
#endif

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  // calibrate the MPU
  uint8_t offsets[6];
  offsets[0] = static_cast<uint8_t>(offset_acel_x >> 8);
  offsets[1] = static_cast<uint8_t>(offset_acel_x & 0x00ff);
  offsets[2] = static_cast<uint8_t>(offset_acel_y >> 8);
  offsets[3] = static_cast<uint8_t>(offset_acel_y & 0x00ff);
  offsets[4] = static_cast<uint8_t>(offset_acel_z >> 8);
  offsets[5] = static_cast<uint8_t>(offset_acel_z & 0x00ff);

  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(XA_OFFS_USRH);
  Wire.write(offsets, 6);

  offsets[0] = static_cast<uint8_t>(offset_gyro_x >> 8);
  offsets[1] = static_cast<uint8_t>(offset_gyro_x & 0x00ff);
  offsets[2] = static_cast<uint8_t>(offset_gyro_y >> 8);
  offsets[3] = static_cast<uint8_t>(offset_gyro_y & 0x00ff);
  offsets[4] = static_cast<uint8_t>(offset_gyro_z >> 8);
  offsets[5] = static_cast<uint8_t>(offset_gyro_z & 0x00ff);

  Wire.write(XG_OFFS_USRH);
  Wire.write(offsets, 6);
  Wire.endTransmission();

  // initialize the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // hide the Adafruit welcome screen
  display.clearDisplay();
  display.display();
}

void loop() {

  // read data from the MPU
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // calculate the roll angle
  static const float rad_to_deg = 180/3.141592654;
  const float cur_roll = atan(a.acceleration.y/a.acceleration.z) * rad_to_deg;

  // update the min/max roll angle values
  min_roll = min(cur_roll, min_roll);
  max_roll = max(cur_roll, max_roll);

#ifdef USE_SERIAL
  Serial.print(a.acceleration.x);
  Serial.print(" ");
  Serial.print(a.acceleration.y);
  Serial.print(" ");
  Serial.print(a.acceleration.z);
  Serial.print(" ");
  Serial.print(g.gyro.x);
  Serial.print(" ");
  Serial.print(g.gyro.y);
  Serial.print(" ");
  Serial.print(g.gyro.z);
  Serial.print(" ");
  Serial.print(min_roll);
  Serial.print(" ");
  Serial.print(cur_roll);
  Serial.print(" ");
  Serial.print(max_roll);
  Serial.println("");
#endif

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(80, 50);
  display.print(fabs(max_roll), 1);

  display.setTextSize(3);
  display.setCursor(0, 10);
  
  if (cur_roll < 0)
    display.print('<');
  else if (cur_roll > 0)
    display.print('>');
  else
    display.print(' ');

  display.setCursor(28, 10);
  float abs_roll = fabs(cur_roll);
  if (abs_roll < 10)
    display.print(' ');
  display.print(abs_roll, 1);
  
  display.setTextSize(2);
  display.setCursor(0, 50);
  display.print(fabs(min_roll), 1);

  display.display();
}
