MCU_TARGET = attiny85
PROGRAMMER = -c usbtiny -p t85
CC         = avr-gcc
CFLAGS     = -g -Wall -mmcu=$(MCU_TARGET)

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)


.PHONY: all clean install

all: main.hex

main.hex: main.elf
	avr-objcopy -Oihex main.elf main.hex

main.elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main.elf

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

install:
	avrdude $(PROGRAMMER) -U main.hex

clean:
	rm *.o main.elf main.hex
