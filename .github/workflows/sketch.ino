#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

RTC_DS1307 rtc;
/*************************************
rc connection GND GND
VCC  5 V
SDA 33. 
SCL 35

********************************************/
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// DEFINE SPI PINS
#define TFT_SCK 7
#define TFT_MOSI 11
#define TFT_RES 8
#define MISO 9
#define TFT_HEIGHT 320
#define TFT_CS   12
#define TFT_DC   14
#define TFT_RST  8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  // Initialize the TFT_ILI9341 display
  tft.begin();
  tft.setRotation(3); // Adjust the rotation if needed
}

void loop() {
  DateTime now = rtc.now();

  Serial.print("Current time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  // Display date and time on the TFT_ILI9341 display
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
tft.setTextColor(ILI9341_CYAN);

  tft.print("Date: ");
  tft.print(now.year(), DEC);
  tft.print('/');
  tft.print(now.month(), DEC);
  tft.print('/');
  tft.print(now.day(), DEC);

  tft.setCursor(0, 50);
  tft.print("Day: ");
  tft.print(daysOfTheWeek[now.dayOfTheWeek()]);

  tft.setTextColor(ILI9341_RED);
  tft.setCursor(0, 100);
  tft.print("Time: ");
  tft.print(now.hour(), DEC);
  tft.print(':');
  tft.print(now.minute(), DEC);
  tft.print(':');
  tft.print(now.second(), DEC);

   tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(0, 140);
  tft.print(" by ARVIND PATIL ");

  delay(3000);
}
