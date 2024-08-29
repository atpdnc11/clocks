#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimeLib.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int clockCenterX = SCREEN_WIDTH / 2;
int clockCenterY = ((SCREEN_HEIGHT - 16) / 2) + 16; // top yellow part is 16 px height
int clockRadius = 33; // Increased radius by 10 pixels

void setup() {
  Serial.begin(115200);
  Serial.println();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display(); // Clear the buffer
  delay(2000);  // Pause for 2 seconds
  display.clearDisplay();   // clears the screen and buffer
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setRotation(0);  // Rotate screen 0 degrees (portrait mode)
}

void loop() {
  display.clearDisplay();   // clears the screen and buffer

  // Draw clock
  analogClockFrame();

  // Print text
  printText("Arvind", 0, 10); // Adjust the position as needed

  display.display();  // Display the content
  delay(1000);  // Pause for a second
}

void analogClockFrame() {
  // Draw the clock face
  display.drawCircle(clockCenterX, clockCenterY, 2, SSD1306_WHITE);
  
  // Hour ticks
  for (int z = 0; z < 360; z += 30) {
    float angle = z;
    angle = (angle / 57.29577951); // Convert degrees to radians
    int x2 = (clockCenterX + (sin(angle) * clockRadius));
    int y2 = (clockCenterY - (cos(angle) * clockRadius));
    int x3 = (clockCenterX + (sin(angle) * (clockRadius - (clockRadius / 8))));
    int y3 = (clockCenterY - (cos(angle) * (clockRadius - (clockRadius / 8))));
    display.drawLine(x2, y2, x3, y3, SSD1306_WHITE);
  }

  // Display second hand
  float angle = second() * 6;
  angle = (angle / 57.29577951); // Convert degrees to radians
  int x3 = (clockCenterX + (sin(angle) * (clockRadius - (clockRadius / 5))));
  int y3 = (clockCenterY - (cos(angle) * (clockRadius - (clockRadius / 5))));
  display.drawLine(clockCenterX, clockCenterY, x3, y3, SSD1306_WHITE);

  // Display minute hand
  angle = minute() * 6;
  angle = (angle / 57.29577951); // Convert degrees to radians
  x3 = (clockCenterX + (sin(angle) * (clockRadius - (clockRadius / 4))));
  y3 = (clockCenterY - (cos(angle) * (clockRadius - (clockRadius / 4))));
  display.drawLine(clockCenterX, clockCenterY, x3, y3, SSD1306_WHITE);

  // Display hour hand
  angle = hour() * 30 + int((minute() / 12) * 6);
  angle = (angle / 57.29577951); // Convert degrees to radians
  x3 = (clockCenterX + (sin(angle) * (clockRadius - (clockRadius / 2))));
  y3 = (clockCenterY - (cos(angle) * (clockRadius - (clockRadius / 2))));
  display.drawLine(clockCenterX, clockCenterY, x3, y3, SSD1306_WHITE);
}

void printText(String text, int x, int y) {
  display.setCursor(x, y);
  display.print(text);
}
