// An hourglass watch driven by the Adafruit Trinket
#include "SSD1306_Display.h"

#define SDA_PIN               0
#define SCL_PIN               2
#define RESET_PIN             1
#define BUTTON_PIN            3

#define TIME_MS 120000
#define ELECTRICITY_TIME 8000

SSD1306_Display display;

// Because the Adafruit Trinket has SCL and INT0 on the same pin we have to swap
// between communication with the OLED and listening for interrupts.
int columns = -1;

void setup() {
    pinMode(SDA_PIN, OUTPUT);
    pinMode(SCL_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    display.init(RESET_PIN);
    display.clear();
    delay(10);
}

void loop() {
    if (columns >= 0) {
        display.display_columns(columns--);
        delay(TIME_MS / SSD1306_WIDTH - ELECTRICITY_TIME / SSD1306_WIDTH); // Width constant from SSD1306_Display.h
    }
    if (digitalRead(BUTTON_PIN) == LOW)
        columns = 128;
}

/*
void beginListenInterrupts() {
    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(0, renewOLED, RISING);
}

void stopListenInterrupts() {
    pinMode(SCL_PIN, OUTPUT);
    detachInterrupt(0);
}
void renewOLED() {
    columns = 128;
}

void renewOLED() {
    if (columns <= 0)
        display.init();

    stopListenInterrupts();
    columns = 128;
    display.display_columns(columns);
}

void countDownOLED() {
    while (columns > 0) {
        // Listen for interrupts while we wait.
        beginListenInterrupts();
        delay(TIME_MS / SSD1306_WIDTH - ELECTRICITY_TIME / SSD1306_WIDTH); // Width constant from SSD1306_Display.h
        stopListenInterrupts();
        display.display_columns(--columns);
    }

    beginListenInterrupts();
}
*/
