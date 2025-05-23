#include <LiquidCrystal.h>
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

// declare the LCD wiring schema used
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// define the masks for the two rows
static char* upper_row = "X:       Y:     ";
static char* lower_row = "Z:       A:     ";

void sprintf_accel(char* buffer, int pos, float value) {
  // convert the floating point value in cents
  int cents = static_cast<int>(value * 100);
  // print the sign
  if (cents >= 0)
    buffer[pos++] = '+';
  else
    buffer[pos++] = '-';
  // print the value, or 9.99 if it is too big
  cents = min(999, labs(cents));
  buffer[pos++] = '0' + cents / 100 % 10; // units
  buffer[pos++] = '.';                    // decimal separator
  buffer[pos++] = '0' + cents /  10 % 10; // tenths
  buffer[pos++] = '0' + cents       % 10; // cents
}

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
  Wire.write(ACCEL_CONFIG);
  Wire.write(afs_sel);
  Wire.endTransmission();

  // set the acceleration conversion factor
  to_g_force = 1. / (16384 >> (afs_sel >> 3 & 0x03));

  // initialize the LCD display
  lcd.begin(16, 2);

  // print the first row template
  lcd.setCursor(0, 0);
  lcd.print(upper_row);

  // print the second row template
  lcd.setCursor(0, 1);
  lcd.print(lower_row);

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

  // convert the accelerometer readings to g-force values
  float accel_x_g = accel_x * to_g_force;
  float accel_y_g = accel_y * to_g_force;
  float accel_z_g = accel_z * to_g_force;

  // calculate the total acceleration
  float a = sqrt(
    accel_x_g * accel_x_g
    + accel_y_g * accel_y_g
    + accel_z_g * accel_z_g);

  // print the acceleration values into the row templates
  sprintf_accel(upper_row,  2, accel_x_g);
  sprintf_accel(upper_row, 11, accel_y_g);
  sprintf_accel(lower_row,  2, accel_z_g);
  sprintf_accel(lower_row, 11, a);

  // update the display
  lcd.setCursor(0, 0);
  lcd.print(upper_row);
  lcd.setCursor(0, 1);
  lcd.print(lower_row);

  // print the acceleration values
  Serial.println(String(accel_x) + ": " + accel_x_g);
  Serial.println(String(accel_y) + ": " + accel_y_g);
  Serial.println(String(accel_z) + ": " + accel_z_g);
  Serial.println(" ");

  // wait some time before the next acquisition
  delay(1000);
}
