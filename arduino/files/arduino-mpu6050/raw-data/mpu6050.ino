#include <Wire.h>

const int8_t MPU_I2C_ADDR = 0x68; // address of the MPU-6050 device

const int8_t ACCEL_CONFIG = 0x1C; // Accelerometer Configuration
const int8_t ACCEL_XOUT_H = 0x3B; // Accelerometer Measurements
const int8_t PWR_MGMT_1   = 0x6B; // Power Management 1 register address

// accelerometer full scale modes
const int8_t AFS_SEL_2G   = 0x00;
const int8_t AFS_SEL_4G   = 0x08;
const int8_t AFS_SEL_8G   = 0x10;
const int8_t AFS_SEL_16G  = 0x18;

float to_g_force;

void setup() {
  // initialize the Wire library
  Wire.begin();

  // wake up the mpu-6050 unit
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission();

  // select the accelerometer full scale
  int8_t afs_sel = AFS_SEL_2G;

  // set the accelerometer full scale
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(afs_sel);
  Wire.write(AFS_SEL_2G);
  Wire.endTransmission();

  // set the acceleration conversion factor
  to_g_force = 1. / (16384 >> (afs_sel >> 3 & 0x03));

  // initialize the serial port
  Serial.begin(9600);
}

void loop() {
  // point to the first accelerometer register
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission();

  // read six bytes of data
  Wire.requestFrom(MPU_I2C_ADDR, 6);

  // the most significant byte is transmitted first!
  int16_t accel_x = Wire.read() << 8 | Wire.read();
  int16_t accel_y = Wire.read() << 8 | Wire.read();
  int16_t accel_z = Wire.read() << 8 | Wire.read();

  // convert accelerometer readings to g-force values
  float accel_x_g = accel_x * to_g_force;
  float accel_y_g = accel_y * to_g_force;
  float accel_z_g = accel_z * to_g_force;

  // print the acceleration values
  Serial.println(String(accel_x) + ": " + accel_x_g);
  Serial.println(String(accel_y) + ": " + accel_y_g);
  Serial.println(String(accel_z) + ": " + accel_z_g);
  Serial.println(" ");

  // wait some time before the next acquisition
  delay(1000);
}
