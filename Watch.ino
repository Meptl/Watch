// An hourglass watch driven by the Adafruit Trinket
#include "SSD1306_Display.h"

#define SDA_PIN               0
#define SCL_PIN               2
#define RESET_PIN             1
#define BUTTON_PIN            3

#define TIME_MS 120000
#define ELECTRICITY_TIME 8000

SSD1306_Display display;
unsigned long prevMillis = 0;
// Width constant from SSD1306_Display.h
// Move a pixel every interval
unsigned long interval = TIME_MS / SSD1306_WIDTH - ELECTRICITY_TIME / SSD1306_WIDTH;
// Amount of time we missed the waiting period by.
unsigned long overTime = 0;

volatile int columns = -1;

// It's not ideal using PCINT for buttons, but on the Adafruit Trinket SCL and
// INT share the same pin
void setup() {
    pinMode(SDA_PIN, OUTPUT);
    pinMode(SCL_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    display.init(RESET_PIN);
    display.clear();
}

void loop() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        prevMillis = millis();
        columns = 128;
        display.display_columns(128);
    }

    if (columns >= 0) {
        unsigned long currentMillis = millis();
        unsigned long deltaMillis = currentMillis - prevMillis;
        if (deltaMillis - overTime > interval) {
            // Time be missed expected interval by.
            overTime = deltaMillis - interval;
            prevMillis = currentMillis;

            display.display_columns(--columns);
        }
    }

    delay(20);
}
