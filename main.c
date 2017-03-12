/* Hello AVR. Flashes LED at 1Hz. */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "SSD1306.h"
#include "USI_TWI_Master.h"
#include "usi_twi.h"

// Pin names are defined in io.h
#define LED      PB0
#define LED_PORT PORTB
#define LED_DDR  DDRB

#define SDA      PB0
#define SCL      PB2

#define SSD1306_RESET PB4


#define BV(x)           (1 << x)
#define setBit(P, B)    P |= BV(B)
#define clearBit(P, B)  P &= ~BV(B)
#define toggleBit(P, B) P ^= BV(B)


int main(void) {
    // Set SDA, SCL for OUTPUT
    setBit(DDRB, SDA);
    setBit(DDRB, SCL);
    setBit(DDRB, SSD1306_RESET);

    // Init screen (initializes I2C)
    _delay_ms(2000);
    SSD1306_init(SSD1306_RESET);

    while (1) {
        //SSD1306_display_columns(28);
        //_delay_ms(500);
        toggleBit(LED_PORT, LED);
        _delay_ms(1000);

    }

    return 0;
}
