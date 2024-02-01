// Northrop Grumman Innovation Lab
// East Coast
// December 2023

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

float calibration_value = 21.34 + 0.78;
int phval = 0;
unsigned long avgval = 0;
int buffer_arr[10], temp;

float ph_act;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long previousMillis = 0;
const unsigned long interval = 500; // Interval in milliseconds

void setup() {
  Wire.begin();
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    for (int i = 0; i < 10; i++) {
      buffer_arr[i] = analogRead(A0);
      delay(30);
    }

    for (int i = 0; i < 9; i++) {
      for (int j = i + 1; j < 10; j++) {
        if (buffer_arr[i] > buffer_arr[j]) {
          temp = buffer_arr[i];
          buffer_arr[i] = buffer_arr[j];
          buffer_arr[j] = temp;
        }
      }
    }

    avgval = 0;
    for (int i = 2; i < 8; i++) {
      avgval += buffer_arr[i];
    }

    float volt = (float)avgval * 5.0 / 1024 / 6;
    ph_act = -5.70 * volt + calibration_value;

    Serial.println("pH Val: ");
    Serial.print(ph_act);
    display_pHValue();
  }
}

void display_pHValue() {
  // Display pH value on the OLED display
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("pH:");

  display.setTextSize(2);
  display.setCursor(55, 0);
  display.print(ph_act);

  display.display();
}
