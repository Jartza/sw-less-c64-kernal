// Simple "switchless" kernal switcher for Commodore 64
// using ATTiny25/45/85 chip.
// 
// (C) 2019 Jari Tulilahti

#include <avr/io.h>
#include <stdint.h>
#include "avr_common.h"

// Make "bit pointers" for input and output pins
#define O_SELECT BITP(PORTB, PB0)
#define I_RESET BITP(PINB, PB1)
#define I_RESTORE BITP(PINB, PB2)

// Make "bit pointers" for data direction registers to pins
#define DIR_SELECT BITP(DDRB, PB0)
#define DIR_RESET BITP(DDRB, PB1)
#define DIR_RESTORE BITP(DDRB, PB2)

int main(void) {
    // MUX input and output pins
    DIR_RESTORE = DIR_IN;
    DIR_RESET = DIR_IN;
    DIR_SELECT = DIR_OUT;

    // Code just busy-loops here. This code makes AVR simulate a simple
    // gated D latch where RESTORE line acts as a data pin and RESET line
    // acts as enable line. Differences to gated D latch is that the 
    // output is ~Q (inverted) and enable is also inverted (enables when
    // RESET low)
    while (1) {
        // As long as RESET-line stays low, keep outputting
        // the RESTORE-line state inverted to output pin.
        while (!I_RESET) {
            O_SELECT = (I_RESTORE ? LEVEL_LOW : LEVEL_HIGH);
        }
        // As long as RESET-line is high, keep output state (do nothing)
        while (I_RESET) {}
    }
}
