// An hourglass watch driven by the Adafruit Trinket
#include "SSD1306_Display.h"
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define SDA_PIN               0
#define OLED_PWR_PIN          1
#define SCL_PIN               2
#define BUTTON_PIN            3
#define RESET_PIN             4

#define TIME_MS 6000
#define ELECTRICITY_TIME 3000

SSD1306_Display display;
unsigned long prevMillis = 0;

// Width constant from SSD1306_Display.h
// Move a pixel every interval
unsigned long interval = TIME_MS / SSD1306_WIDTH - ELECTRICITY_TIME / SSD1306_WIDTH;

volatile int columns = -1;

// It's not ideal using PCINT for buttons, but on the Adafruit Trinket SCL and
// INT share the same pin
void setup() {
    pinMode(SDA_PIN, OUTPUT);
    pinMode(SCL_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);
    pinMode(OLED_PWR_PIN, OUTPUT);
    digitalWrite(OLED_PWR_PIN, HIGH);

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pciSetup();
}

void loop() {
    if (columns >= 0) {
        unsigned long currentMillis = millis();
        unsigned long deltaMillis = currentMillis - prevMillis;
        if (deltaMillis > interval) {
            prevMillis = currentMillis;

            display.display_columns(--columns);
        }
    } else {
        sleep_device();
    }
}

void sleep_device() {
    digitalWrite(OLED_PWR_PIN, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();   // Goes to sleep
    sleep_disable();
    digitalWrite(OLED_PWR_PIN, HIGH);
    display.init(RESET_PIN);
}

void pciSetup() {
    cli();              // Disable interrupts
    GIMSK = 0b00100000; // Turns on pin change interrupts
    PCMSK = 0b00001000; // Turns on PCINT3
    sei();              // Enable interrupts
}

ISR(PCINT0_vect) {
    if (digitalRead(BUTTON_PIN) == LOW)
        columns = 128;
}
