# Simple makefile for Switchless kernal switcher
# (C) 2019 Jari Tulilahti
# 
# Set PROGRAMMER to match your AVR programmer
# and set DEVICE to either attiny25, attiny45 or attiny85 
# depending of the chip you are using
# 
DEVICE     = attiny85
PROGRAMMER = usbasp

# options below should not be changed until you know what you are doing
#
CLOCK      = 1000000
FUSES      = -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
OBJECTS    = main.o
AVRDUDE = avrdude -c $(PROGRAMMER) -p $(DEVICE) -B4
COMPILE = avr-gcc -Wall -Os -std=gnu99 -flto -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

clean:
	rm -f main.hex main.elf $(OBJECTS)

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

# debugging
disasm:	main.elf
	avr-objdump -d main.elf
