/* ATtiny85 as an I2C Master          BroHogan                      1/21/11
 */

#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#include "SSD1306_Display.h"

#define SDA_PIN                 0
#define SCL_PIN                  2
#define RESET_PIN             1

#define SSD1306_HEIGHT  128
#define SSD1306_WIDTH   32

SSD1306_Display display;

void setup(){
  pinMode(SDA_PIN,OUTPUT);
  pinMode(SCL_PIN,OUTPUT);
  pinMode(RESET_PIN,OUTPUT);
  display.init(RESET_PIN);
display.display();
}


void loop(){
}
