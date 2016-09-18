// An hourglass watch driven by the Adafruit Trinket
#include "SSD1306_Display.h"
#include <avr/interrupt.h>

#define SDA_PIN               0
#define SCL_PIN               2
#define RESET_PIN             1
#define BUTTON_PIN            3

#define TIME_MS 120000
#define ELECTRICITY_TIME 8000

SSD1306_Display display;

volatile int columns = -1;

// It's not ideal using PCINT for buttons, but on the Adafruit Trinket SCL and
// INT share the same pin
void setup() {
    pinMode(SDA_PIN, OUTPUT);
    pinMode(SCL_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pciSetup();

    display.init(RESET_PIN);
    display.clear();
    delay(10);
}

void loop() {
    if (columns >= 0) {
        display.display_columns(columns--);
        delay(TIME_MS / SSD1306_WIDTH - ELECTRICITY_TIME / SSD1306_WIDTH); // Width constant from SSD1306_Display.h
    }
}

void pciSetup() {
    cli();              // Disable interrupts
    GIMSK = 0b00100000; // Turns on pin change interrupts
    PCMSK = 0b00001000; // Turns on PCINT3
    sei();              // Enable interrupts
}

ISR(PCINT0_vect) {
    delay(10); // Wait for debounce?
    if (digitalRead(BUTTON_PIN) == LOW)
        columns = 128;
}
