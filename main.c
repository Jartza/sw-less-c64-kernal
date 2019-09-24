#include "avr_common.h"
#include <avr/io.h>

#define I_RESTORE BITP(PINB, PB0)
#define I_RESET BITP(PINB, PB1)
#define O_SELECT BITP(PORTB, PB2)

#define DIR_RESTORE BITP(DDRB, PB0)
#define DIR_RESET BITP(DDRB, PB1)
#define DIR_SELECT BITP(DDRB, PB2)

int main(void) {
    DIR_RESTORE = DIR_IN;
    DIR_RESET = DIR_IN;
    DIR_SELECT = DIR_OUT;
    while (1) {
        // As long as RESET stays low, keep changing output state according to input
        while (!I_RESET) {
            O_SELECT = (I_RESTORE ? LEVEL_LOW : LEVEL_HIGH);
        }
        // As long as RESET is high, do nothing
        while (I_RESET) {}
    }
}
