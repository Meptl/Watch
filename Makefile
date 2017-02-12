CFLAGS=-g -mmcu=attiny85
CC=avr-gcc

OBJECTS = $(patsubst %.c, %.o $(wildcard *.c))
HEADERS = $(wildcard *.h)

#$(CC) $(CFLAGS) main.c -o main.elf
#avr-objcopy -Oihex main.elf main.hex

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -o $@

clean:
	rm *.o
	rm $(TARGET)
