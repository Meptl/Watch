#include "SSD1306_Display.h"

#define SDA_PIN                 0
#define SCL_PIN                  2
#define RESET_PIN             1

#define TIME_MS 60000

SSD1306_Display display;

void setup(){
  pinMode(SDA_PIN,OUTPUT);
  pinMode(SCL_PIN,OUTPUT);
  pinMode(RESET_PIN,OUTPUT);
  display.init(RESET_PIN);
  delay(1000);
}

int columns = 0;

void loop(){
  delay(TIME_MS / SSD1306_WIDTH); // Width constant from SSD1306_Display.h
    display.display_columns(columns++);
}
