#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int8_t MPU_I2C_ADDR = 0x68; // address of the MPU-6050 device

const int8_t XG_OFFS_USRH = 0x06; // Accelerometer Offset Cancellation
const int8_t ACCEL_CONFIG = 0x1C; // Accelerometer Configuration
const int8_t ACCEL_XOUT_H = 0x3B; // Accelerometer Measurements
const int8_t PWR_MGMT_1   = 0x6B; // Power Management 1 register address

// accelerometer full scale modes
const int8_t AFS_SEL_2G   = 0x00;
const int8_t AFS_SEL_4G   = 0x08;
const int8_t AFS_SEL_8G   = 0x10;
const int8_t AFS_SEL_16G  = 0x18;

volatile int8_t afs_sel;
volatile int8_t new_afs_sel;
volatile bool emulate_1g_afs;

// declare the OLED display used
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
const int display_refresh_rate_ms = 250;     // update the display every 250ms
unsigned long last_display_refresh_time = 0; // last time the display was updated

// the cursor
static const int cursor_radius = 4;

// the grid
static const int grid_width  = 112;
static const int grid_height =  42;

static const unsigned char PROGMEM grid_bitmap[] = {
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000101, B01010101,
   B01010101, B01010000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000001, B01010000, B00000000,
   B00000000, B00000101, B01000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B01011100, B00000000, B00000001,
   B00000000, B00000000, B00011010, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00001111, B00001000, B00000000, B00000000,
   B00000000, B00000000, B00010000, B11110000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B11100000, B00000000, B00000000, B00000000,
   B10000000, B00000000, B00000000, B00000111, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000110, B00000000, B00100000, B00000000, B00000000,
   B00000000, B00000000, B00000100, B00000000, B01100000, B00000000, B00000000,
  B00000000, B00000000, B00110000, B00000000, B00000000, B00000000, B00000001,
   B00000000, B00000000, B00000000, B00000000, B00001100, B00000000, B00000000,
  B00000000, B00000000, B10000000, B00000000, B10000000, B00000000, B00000000,
   B00000000, B00000000, B00000001, B00000000, B00000001, B00000000, B00000000,
  B00000000, B00000010, B00000000, B00000000, B00000000, B00000000, B00000000,
   B10000000, B00000000, B00000000, B00000000, B00000000, B01000000, B00000000,
  B00000000, B00001000, B00000000, B00000010, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B01000000, B00000000, B00010000, B00000000,
  B00000000, B00100010, B00100010, B00100000, B01000100, B01000100, B01000101,
   B00100010, B00100010, B00100010, B00000100, B01000100, B01000100, B00000000,
  B00000000, B10000000, B00000000, B00001000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00010000, B00000000, B00000001, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
   B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000010, B00000000, B00000000, B00100000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000100, B00000000, B00000000, B01000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
   B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00001000, B00000000, B00000000, B10000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000001, B00000000, B00000000, B00010000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
   B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00010000, B00000000, B00000010, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B01000000, B00000000, B00001000,
  B00100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
   B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000100,
  B00100000, B00000000, B00001000, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00010000, B00000000, B00000100,
  B00110001, B00010001, B00000001, B00010001, B00010001, B00010001, B00010000,
   B10001000, B10001000, B10001000, B10001000, B10000001, B00010001, B00010100,
  B00100000, B00000000, B00100000, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00000100, B00000000, B00000100,
  B00100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
   B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000100,
  B00010000, B00000000, B10000000, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00000001, B00000000, B00001000,
  B00010000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
   B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001000,
  B00001000, B00000010, B00000000, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00000000, B01000000, B00010000,
  B00000100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
   B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00100000,
  B00000010, B00001000, B00000000, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00000000, B00010000, B01000000,
  B00000001, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
   B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B10000000,
  B00000000, B10100000, B00000000, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00000000, B00000101, B00000000,
  B00000000, B01101000, B10001000, B10001000, B10001000, B10001000, B10001001,
   B00010001, B00010001, B00010001, B00010001, B00010001, B00010110, B00000000,
  B00000000, B00001000, B00000000, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00000000, B00011000, B00000000,
  B00000000, B00000110, B00000000, B00000000, B00000000, B00000000, B00000000,
   B10000000, B00000000, B00000000, B00000000, B00000000, B01100000, B00000000,
  B00000000, B00000001, B10000000, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00000001, B10000000, B00000000,
  B00000000, B00000000, B01100000, B00000000, B00000000, B00000000, B00000001,
   B00000000, B00000000, B00000000, B00000000, B00000110, B00000000, B00000000,
  B00000000, B00000000, B00011100, B00000000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00000000, B00111000, B00000000, B00000000,
  B00000000, B00000000, B00000011, B10000000, B00000000, B00000000, B00000000,
   B10000000, B00000000, B00000000, B00000001, B11000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B01110000, B00000000, B00000000, B00000000,
   B00000000, B00000000, B00000000, B00001110, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00001111, B00000000, B00000000, B00000001,
   B00000000, B00000000, B00000000, B11110000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B11111000, B00000000, B00000000,
   B00000000, B00000000, B00011111, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000111, B11111000, B00000000,
   B10000000, B00011111, B11100000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000111, B11111111,
   B11111111, B11100000, B00000000, B00000000, B00000000, B00000000, B00000000,
};

// data acquisition rate
const unsigned long scan_rate_ms = 10;       // sample at 100Hz

// data buffers
const int buffer_length = 20;

int16_t accel_x_buffer[buffer_length];
int16_t accel_y_buffer[buffer_length];
float accel_a_buffer[buffer_length];

int next_scan_index = 0;                     // where the next sample will be saved

// interrupt handler
void changeScale() {
  if (afs_sel == AFS_SEL_2G) {
    if (emulate_1g_afs == true)
      emulate_1g_afs = false; // switch from fake 1g to actual 2g scale
    else
      new_afs_sel = AFS_SEL_4G;
  }
  else if (afs_sel == AFS_SEL_4G)
    new_afs_sel = AFS_SEL_8G;
  else if (afs_sel == AFS_SEL_8G)
    new_afs_sel = AFS_SEL_16G;
  else if (afs_sel == AFS_SEL_16G) {
    new_afs_sel = AFS_SEL_2G;
    emulate_1g_afs = true; // back to fake 1g scale
  }
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
  afs_sel = AFS_SEL_2G;
  new_afs_sel = afs_sel;

  // start with the fake 1g scale
  emulate_1g_afs = true;

  // set the accelerometer full scale
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(ACCEL_CONFIG);
  Wire.write(afs_sel);
  Wire.endTransmission();

  // calibrate the accelerometer
  const int16_t offset_x = -2574;
  const int16_t offset_y =   336;
  const int16_t offset_z =  1755;
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(XG_OFFS_USRH);

  uint8_t offsets[6];
  offsets[0] = static_cast<uint8_t>(offset_x >> 8);
  offsets[1] = static_cast<uint8_t>(offset_x & 0x00ff);
  offsets[2] = static_cast<uint8_t>(offset_y >> 8);
  offsets[3] = static_cast<uint8_t>(offset_y & 0x00ff);
  offsets[4] = static_cast<uint8_t>(offset_z >> 8);
  offsets[5] = static_cast<uint8_t>(offset_z & 0x00ff);

  Wire.write(offsets, 6);
  Wire.endTransmission();

  // initialize the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // hide the Adafruit welcome screen
  display.clearDisplay();
  display.display();

  // attach the interrupt handler
  const byte changeScalePin = 3;
  pinMode(changeScalePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(changeScalePin), changeScale, FALLING);
}

void loop() {
  unsigned long loop_start = millis();

  // change the accelerometer scale if requested
  if (new_afs_sel != afs_sel) {
    afs_sel = new_afs_sel;
    // set the accelerometer full scale
    Wire.beginTransmission(MPU_I2C_ADDR);
    Wire.write(ACCEL_CONFIG);
    Wire.write(afs_sel);
    Wire.endTransmission();
  }

  // point to the first accelerometer register
  Wire.beginTransmission(MPU_I2C_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission();

  // read four bytes of data
  Wire.requestFrom(MPU_I2C_ADDR, 4);

  // the most significant byte is transmitted first!
  int16_t accel_x = Wire.read() << 8 | Wire.read();
  int16_t accel_y = Wire.read() << 8 | Wire.read();

  // calculate the total acceleration
  float accel_a = sq(accel_x) + sq(accel_y);

  // save the acceleration data
  accel_x_buffer[next_scan_index] = accel_x;
  accel_y_buffer[next_scan_index] = accel_y;
  accel_a_buffer[next_scan_index] = accel_a;

  // find the position for the next scan
  next_scan_index = (next_scan_index + 1) % buffer_length;

  // time to update the display?
  if (millis() - last_display_refresh_time > display_refresh_rate_ms) {
    // time to update the display
    last_display_refresh_time = millis();

    // find the maximum acceleration index
    int max_scan_index = 0;

    for (int i = 1; i < buffer_length; i++)
      if (accel_a_buffer[i] > accel_a_buffer[max_scan_index])
        max_scan_index = i;

    // clear the drawing area
    display.clearDisplay();

    // load the grid image
    display.drawBitmap(
      (display.width()  - grid_width ) / 2, // x
      (display.height() - grid_height) / 2, // y
      grid_bitmap,
      grid_width,
      grid_height,
      WHITE);

    // print the current accelerometer scale
    display.setCursor(0, display.height() - 8);
    display.setTextColor(WHITE);
    display.print("FS=");
    if (emulate_1g_afs)
        display.print(1);
    else
      display.print(2 << ((afs_sel >> 3) & 0x03));
    display.print("g");

    // plot the cursor
    int32_t x = accel_y_buffer[max_scan_index] >> (emulate_1g_afs ? 8 :  9);
    int32_t y = accel_x_buffer[max_scan_index] >> (emulate_1g_afs ? 9 : 10);

    display.fillCircle(
      64 - (x - x / 8),
      32 - (y - y / 3),
      cursor_radius,
      WHITE);

    // refresh the display
    display.display();
  }

  // wait for the acquisition period to expire
  unsigned long elapsed = millis() - loop_start;

  if (elapsed < scan_rate_ms)
    delay(scan_rate_ms - elapsed);
}
