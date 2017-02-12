/*
 * Adapted from works by CoPiino Electronics and Limor Fried/Ladyada from Adafruit Industries.
 * BSD license, check license.txt for more information
 */
// See SSD1306 datasheet for multi-byte commands
#ifndef SSD1306_H_
#define SSD1306_H_

// Config
#define SSD1306_ADDR   0x3C
#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT 32


#define SSD1306_CMDMODE		      0x80
#define SSD1306_DATAMODE	      0x40
#define SSD1306_SETSTARTLINE	      0x40

// Fundamental Commands
#define SSD1306_SETCONTRAST           0x81     // Double byte command to select 1 out of 256 contrast steps. Default(RESET = 0x7F)
#define SSD1306_DISPLAYALLON_RESUME   0xA4     // Resume to RAM content display(RESET), Output follows RAM content
#define SSD1306_DISPLAYALLON          0xA5     // Entire display ON, Output ignores RAM content
#define SSD1306_NORMALDISPLAY	      0xA6     // Normal display (RESET)
#define SSD1306_INVERTDISPLAY	      0xA7     // Inverse display
#define SSD1306_DISPLAYOFF	      0xAE     // Sleep mode(RESET)
#define SSD1306_DISPLAYON	      0xAF     // Normal mode

// Scrolling Commands
#define SSD1306_LEFT_SCROLL			  0x00
#define SSD1306_RIGHT_SCROLL			  0x01
#define SSD1306_RIGHT_HORIZONTAL_SCROLL           0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL            0x27
#define SSD1306_VERTICAL_RIGHT_HORIZONTAL_SCROLL  0x29
#define SSD1306_VERTICAL_LEFT_HORIZONTAL_SCROLL   0x2A
#define SSD1306_ACTIVATE_SCROLL                   0x2F
#define SSD1306_DEACTIVATE_SCROLL                 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA          0xA3

// Addressing Setting Commands
#define SSD1306_MEMORYMODE                0x20
#define SSD1306_HORIZONTAL_MODE	          0x00
#define SSD1306_VERTICAL_MODE	          0x01
#define SSD1306_PAGE_MODE	          0x02
#define SSD1306_COLUMNADDR                0x21       // Setup column start and end address. This command is only for horizontal or vertical addressing mode
#define SSD1306_PAGEADDR                  0x22       // Setup page start and end address. This command is only for horizontal or vertical addressing mode

//Hardware Configuration (Panel resolution & layout related) Commands
#define SSD1306_SEGREMAPCMD               0xA1       // Column address 127 is mapped to SEG0
#define SSD1306_SEGREMAP                  0xA0       // Default. column address 0 is mapped to SEG0(RESET)
#define SSD1306_SETMULTIPLEX              0xA8       // Set MUX ratio to N+1 MUX
#define SSD1306_COMSCANINC                0xC0       // Normal mode (RESET). Scan from COM0 to COM[N-1]
#define SSD1306_COMSCANDEC                0xC8       // Remapped mode. Scan from COM[N-1] to COM0
#define SSD1306_SETDISPLAYOFFSET          0xD3       // Set vertical shift by COM from 0d~63d. The value is reset to 00h after RESET.
#define SSD1306_SETCOMPINS                0xDA

//Timing & Driving Scheme Setting Commands
#define SSD1306_SETDISPLAYCLOCKDIV        0xD5
#define SSD1306_SETPRECHARGE              0xD9
#define SSD1306_SETVCOMDETECT             0xDB
#define SSD1306_NOOP                      0xE3

#define SSD1306_CHARGEPUMP      	  0x8D
#define SSD1306_CHARGEPUMP_ENABLE	  0x14
#define SSD1306_CHARGEPUMP_DISABLE        0x10     //default


#define SSD1306_Scroll_2Frames			      0x7
#define SSD1306_Scroll_3Frames			      0x4
#define SSD1306_Scroll_4Frames			      0x5
#define SSD1306_Scroll_5Frames			      0x0
#define SSD1306_Scroll_25Frames			      0x6
#define SSD1306_Scroll_64Frames			      0x1
#define SSD1306_Scroll_128Frames		      0x2
#define SSD1306_Scroll_256Frames		      0x3

#define SSD1306_EXTERNALVCC  0x1
#define SSD1306_SWITCHCAPVCC 0x2

void SSD1306_init(uint8_t);
void SSD1306_init_screen(void);
void SSD1306_clear(void);
void SSD1306_display_columns(int count);

#endif
