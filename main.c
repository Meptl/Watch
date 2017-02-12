/* Hello AVR. Flashes LED at 1Hz. */
#include <avr/io.h>
#include <util/delay.h>
#include "SSD1306.h"

// Pin names are defined in io.h
#define LED      PB0
#define LED_PORT PORTB
#define LED_DDR  DDRB

#define SSD1306_RESET PB4

#define BV(x)           (1 << x)
#define setBit(P, B)    P |= BV(B)
#define clearBit(P, B)  P &= ~BV(B)
#define toggleBit(P, B) P ^= BV(B)


int main(void) {

    setBit(LED_DDR, LED); // set LED for output
    SSD1306_init(SSD1306_RESET);


    while (1) {
        toggleBit(LED_PORT, LED);

        _delay_ms(500);

    }

    return 0;
}
