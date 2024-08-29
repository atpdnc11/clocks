#include <Arduino.h>
#include <U8g2lib.h> // u8g2 library for drawing on OLED display - needs to be installed in Arduino IDE first
#include <Wire.h> // wire library for IIC communication with the OLED display
#include <RTClib.h> // RTC library for real-time clock

//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0); // set the OLED display to 128x64px, HW IIC, no rotation, used in WOKWI
U8G2_SH1107_128X128_1_HW_I2C u8g2(U8G2_R0); // final display, 128x128px [page buffer, size = 128 bytes], HW IIC connection

RTC_DS3231 rtc; // create an RTC object

// IIC connection of the OLED display and Arduino UNO
// +5V > +5V
// GND > GND
// SCL (serial clock) > A5 or SCL
// SDA (serial data) > A4 or SDA

void setup(void) {
  u8g2.begin();  // begin the u8g2 library
  u8g2.setContrast(255); // set display contrast/brightness

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // set RTC to the date & time this sketch was compiled
  }
}

void loop(void) {
  DateTime now = rtc.now(); // get the current date and time

  int hours = now.hour();
  int minutes = now.minute();
  int seconds = now.second();

  // Calculate angles
  float hourAngle = (hours % 12 + minutes / 60.0) * 30; // 360 / 12 = 30 degrees per hour
  float minuteAngle = (minutes + seconds / 60.0) * 6; // 360 / 60 = 6 degrees per minute
  float secondAngle = seconds * 6; // 360 / 60 = 6 degrees per second

  // Calculate hand positions
  int hourX = 64 + 30 * cos(radians(hourAngle - 90)); // length of hour hand is 30
  int hourY = 64 + 30 * sin(radians(hourAngle - 90));
  int minuteX = 64 + 45 * cos(radians(minuteAngle - 90)); // length of minute hand is 45
  int minuteY = 64 + 45 * sin(radians(minuteAngle - 90));
  int secondX = 64 + 55 * cos(radians(secondAngle - 90)); // length of second hand is 55
  int secondY = 64 + 55 * sin(radians(secondAngle - 90));

  u8g2.firstPage(); // select the first page of the display (page is 128x8px), since we are using the page drawing method of the u8g2 library
  do {
    // Draw clock face
    u8g2.drawCircle(64, 64, 60, U8G2_DRAW_ALL); // draw the outer circle of the clock
    u8g2.drawCircle(64, 64, 2, U8G2_DRAW_ALL); // draw the center circle of the clock

    // Draw clock hands
    u8g2.drawLine(64, 64, hourX, hourY); // draw hour hand
    u8g2.drawLine(64, 64, minuteX, minuteY); // draw minute hand
    u8g2.drawLine(64, 64, secondX, secondY); // draw second hand

  } while (u8g2.nextPage()); // go over all the pages until the whole display is updated

  delay(1000); // wait for 1 second before refreshing the display
}
