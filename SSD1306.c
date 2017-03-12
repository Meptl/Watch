/*
 * Adapted from works by CoPiino Electronics and Limor Fried/Ladyada from Adafruit Industries.
 * BSD license, check license.txt for more information
 */

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "SSD1306.h"
#include "usi_twi.h"

// Pin names are defined in io.h
#define RESET_PORT PORTB
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

void send_command(uint8_t command)
{
    twi_begin_transmission(SSD1306_ADDR);
    twi_send(0x00); // Control character
    twi_send(command);
    twi_end_transmission();
}

void send_data(unsigned char data)
{
    twi_begin_transmission(SSD1306_ADDR);
    twi_send(SSD1306_DATAMODE);
    twi_send(data);
    twi_end_transmission();
}

// Try battery power. Try a different chip.
void SSD1306_init(uint8_t reset_pin)
{
    twi_init();

    // Initial reset
    /*
    setBit(DDRB, reset_pin);
    setBit(RESET_PORT, reset_pin);
    _delay_ms(1);
    clearBit(RESET_PORT, reset_pin);
    _delay_ms(10);
    setBit(RESET_PORT, reset_pin);
    _delay_ms(1);
    */

    // Send configuration commands
    send_command(SSD1306_DISPLAYOFF);

    /*
    send_command(SSD1306_SETMULTIPLEX);
    send_command(0x1F);

    send_command(SSD1306_SETDISPLAYOFFSET);
    send_command(0x0);

    send_command(SSD1306_MEMORYMODE);
    send_command(SSD1306_HORIZONTAL_MODE);

    send_command(SSD1306_SETSTARTLINE);

    //send_command(SSD1306_SETCONTRAST);
    //send_command(0x8F);
    //
    send_command(SSD1306_SEGREMAPCMD);

    send_command(SSD1306_COMSCANDEC);
    send_command(SSD1306_NORMALDISPLAY);

    send_command(SSD1306_SETDISPLAYCLOCKDIV);
    send_command(0x80);  // the suggested ratio 0x80

    send_command(SSD1306_SETPRECHARGE);
    //send_command(0x22); // Send for external VCC
    send_command(0xF1); // Send for switch cap VCC
    send_command(SSD1306_SETCOMPINS);
    send_command(0x02);

    send_command(SSD1306_SETVCOMDETECT);
    send_command(0x40);

    send_command(SSD1306_CHARGEPUMP);
    //send_command(SSD1306_CHARGEPUMP_DISABLE); // Send for external VCC
    send_command(SSD1306_CHARGEPUMP_ENABLE); // Send for switch cap VCC

    send_command(SSD1306_DISPLAYON);
    //*/
}

// Sends a preample for screen output.
void SSD1306_init_screen(void) {
    send_command(SSD1306_COLUMNADDR);
    send_command(0);                 // Column start address (0 = reset)
    send_command(SSD1306_WIDTH - 1); // Column end address (127 = reset)

    send_command(SSD1306_PAGEADDR);
    send_command(0); // Page start address (0 = reset)
    send_command(3); // Page end address
}

// Pushes a blank screen to the OLED
void SSD1306_clear(void) {
    //init_screen();
    for (uint16_t i = 0; i < SSD1306_WIDTH * SSD1306_HEIGHT / 8; i += 16)
    {
        // Send 16 bytes in one transmission
        twi_begin_transmission(SSD1306_ADDR);
        twi_send(SSD1306_DATAMODE);

        for (uint8_t j = 0; j < 16; j++)
            twi_send(0x00);

        twi_end_transmission();
    }
}

// Displays n columns onto the display
// Pages act as rows. Each byte fills a column.
//
// Show N columns beginning on the left.
// This function assumes a WIDTH of 128 pixels.
#define PAGES 4
#define MESSAGE_SIZE 16
void SSD1306_display_columns(int count) {
    if (count <= 0)
       SSD1306_clear();
    //init_screen();

    for (int i = 0; i < PAGES; i++) {
        for (int j = 0; j < SSD1306_WIDTH / MESSAGE_SIZE; j++) {
            twi_begin_transmission(SSD1306_ADDR);
            twi_send(SSD1306_DATAMODE);

            for (int k = 0; k < MESSAGE_SIZE; k++) {
                if (j * MESSAGE_SIZE + k < count)
                    twi_send(0xFF);
                else
                    twi_send(0x00);
            }

            twi_end_transmission();
        }
    }
}
