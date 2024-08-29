#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8
#define scl        4
#define mosi       6
#define ss         7

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

int hours = 9;
int minutes = 30;
int seconds = 0;
char *number[12]={"6","5","4","3","2","1","12","11","10","9","8","7"};
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
float radius = min(SCREEN_HEIGHT, SCREEN_WIDTH)/2-1;

const int X_CENTER = SCREEN_WIDTH / 2;
const int Y_CENTER = SCREEN_HEIGHT / 2;

double angle;
int prevSeconds = -1;
int prevMinutes = -1;
int prevHours = -1;

void drawClockHand(double angle, int length, uint16_t color) {
  int x2 = X_CENTER + (sin(angle) * length);
  int y2 = Y_CENTER - (cos(angle) * length);
  tft.drawLine(X_CENTER, Y_CENTER, x2, y2, color);
}

void draw(void) {
  if (seconds != prevSeconds) {
    if (prevSeconds != -1) {
      drawClockHand(prevSeconds * 6 * 0.0174533, radius - 1, ILI9341_BLACK);  // Erase previous second hand
    }
    drawClockHand(seconds * 6 * 0.0174533, radius - 1, ILI9341_RED);
    prevSeconds = seconds;
  }

  if (minutes != prevMinutes) {
    if (prevMinutes != -1) {
      drawClockHand(prevMinutes * 6 * 0.0174533, radius - 10, ILI9341_BLACK);  // Erase previous minute hand
    }
    drawClockHand(minutes * 6 * 0.0174533, radius - 10, ILI9341_GREEN);
    prevMinutes = minutes;
  }

  if (hours != prevHours) {
    if (prevHours != -1) {
      drawClockHand(prevHours * 30 * 0.0174533 + (prevMinutes / 12.0 * 6 * 0.0174533), radius / 2, ILI9341_BLACK);  // Erase previous hour hand
    }
    drawClockHand(hours * 30 * 0.0174533 + (minutes / 12.0 * 6 * 0.0174533), radius / 2, ILI9341_BLUE);
    prevHours = hours;
  }
}

void setup(void) {
  tft.begin();
  tft.setRotation(3);  // Landscape mode
  tft.fillScreen(ILI9341_BLACK);  // Clear screen
  tft.drawCircle(X_CENTER, Y_CENTER, 1, ILI9341_WHITE);  // Draw center dot
  
  // Draw minute's ticks (60 lines)
  for(int j=1; j<=60; j++){
    angle = j * 6 * 0.0174533;
    int x1 = X_CENTER + (sin(angle) * radius);
    int y1 = Y_CENTER + (cos(angle) * radius);
    int x2 = X_CENTER + (sin(angle) * radius);
    int y2 = Y_CENTER + (cos(angle) * radius);
    tft.drawLine(x1, y1, x2, y2, ILI9341_WHITE);
  }
  
  // Draw hour's ticks (12 lines)
  for(int j=0; j<12; j++){
    angle = j * 30 * 0.0174533;
    int x1 = X_CENTER + (sin(angle) * radius);
    int y1 = Y_CENTER + (cos(angle) * radius);
    int x2 = X_CENTER + (sin(angle) * (radius - 4));
    int y2 = Y_CENTER + (cos(angle) * (radius - 4));
    tft.drawLine(x1, y1, x2, y2, ILI9341_WHITE);
    
    // Draw hour digits (12 lines)
    x2 = X_CENTER + (sin(angle) * (radius - 8));
    y2 = Y_CENTER + (cos(angle) * (radius - 8));
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(x2-6, y2-8);
    tft.print(number[j]);
 
 
  tft.setTextSize(2); 
  tft.setTextColor(ILI9341_YELLOW);
 tft.setCursor(X_CENTER - 30, Y_CENTER + 40);
  tft.print("Arvind");
 
  }
}

void loop(void) {
  seconds += 1;
  if (seconds == 60) { 
    seconds = 0; 
    minutes += 1;
  }
  if (minutes == 60) { 
    minutes = 0; 
    hours += 1;
  }
  if (hours == 24) {
    hours = 1;
  }
  
  draw();
  
  delay(1000);
}
