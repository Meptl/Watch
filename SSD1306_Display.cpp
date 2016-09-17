/*
 * Adapted from works by CoPiino Electronics and Limor Fried/Ladyada from Adafruit Industries.
 * BSD license, check license.txt for more information
 */

#include "SSD1306_Display.h"

#include <stdlib.h>

// Adafruit trinket only has 512 bytes of RAM and cannot fully store a display buffer.
// Otherwise we could simply have a display function that pushes the buffer out.
//static uint8_t buffer[SSD1306_HEIGHT * SSD1306_WIDTH / 8];

void SSD1306_Display::send_command(uint8_t command)
{
    TinyWireM.beginTransmission(SSD1306_ADDR);
    TinyWireM.send(0x00); // Control character
    TinyWireM.send(command);
    TinyWireM.endTransmission();
}

void SSD1306_Display::send_data(unsigned char data)
{
    TinyWireM.beginTransmission(SSD1306_ADDR);
    TinyWireM.send(SSD1306_DATAMODE);
    TinyWireM.send(data);
    TinyWireM.endTransmission();
}

void SSD1306_Display::init(uint8_t reset_pin)
{
    TinyWireM.begin();

    // Initial reset
    pinMode(reset_pin, OUTPUT);
    digitalWrite(reset_pin, HIGH);
    delay(1);
    digitalWrite(reset_pin, LOW);
    delay(10);
    digitalWrite(reset_pin, HIGH);
    delay(1);

    // Send configuration commands
    send_command(SSD1306_DISPLAYOFF);

    send_command(SSD1306_SETMULTIPLEX);
    send_command(0x1F);

    send_command(SSD1306_SETDISPLAYOFFSET);
    send_command(0x0);

    send_command(SSD1306_MEMORYMODE);
    send_command(SSD1306_HORIZONTAL_MODE);

    send_command(SSD1306_SETSTARTLINE);

    send_command(SSD1306_SETCONTRAST);
    send_command(0x8F);

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
}

// Sends a preample for screen output.
void SSD1306_Display::init_screen() {
    send_command(SSD1306_COLUMNADDR);
    send_command(0);                 // Column start address (0 = reset)
    send_command(SSD1306_WIDTH - 1); // Column end address (127 = reset)

    send_command(SSD1306_PAGEADDR);
    send_command(0); // Page start address (0 = reset)
    send_command(3); // Page end address
}

// Pushes a blank screen to the OLED
void SSD1306_Display::clear() {
    //init_screen();
    for (uint16_t i = 0; i < SSD1306_WIDTH * SSD1306_HEIGHT / 8; i += 16)
    {
        // Send 16 bytes in one transmission
        TinyWireM.beginTransmission(SSD1306_ADDR);
        TinyWireM.send(SSD1306_DATAMODE);

        for (uint8_t j = 0; j < 16; j++)
            TinyWireM.send(0x00);

        TinyWireM.endTransmission();
    }
}

// The display is filled in a strange way, see documentation for a more in
//
// Perhaps Vertical memory mode would be better for this. I could not get it to
// work reasonably though.
//
// Show N columns beginning on the left.
// This function assumes a WIDTH of 128 pixels.
#define MESSAGE_SIZE 16
void SSD1306_Display::display_columns(int count) {
    if (count < 0 || count > 128)
        return;
    //init_screen();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < SSD1306_WIDTH / MESSAGE_SIZE; j++) {
            TinyWireM.beginTransmission(SSD1306_ADDR);
            TinyWireM.send(SSD1306_DATAMODE);

            for (int k = 0; k < MESSAGE_SIZE; k++) {
                if (j * MESSAGE_SIZE + k < count)
                    TinyWireM.send(0xFF);
                else
                    TinyWireM.send(0x00);
            }

            TinyWireM.endTransmission();
        }
    }
}
