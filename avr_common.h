/*    Common bit handling macros for AVR (avr-gcc)
 *
 *    (C) Jari Tulilahti
 *
 */

// Struct to handle bits in registers
typedef struct {
	uint8_t b0:1;
	uint8_t b1:1;
	uint8_t b2:1;
	uint8_t b3:1;
	uint8_t b4:1;
	uint8_t b5:1;
	uint8_t b6:1;
	uint8_t b7:1;
} bitmask_s;

// Helper macros for bit pointer macro
#define BNAME(x) BSTR(x)
#define BSTR(x) b##x

// Bit pointer macro which can be used to make individual
// bit variables
#define BITP(var, bit) ((volatile bitmask_s*)&var)->BNAME(bit)

// Bit-Shift-Or macros for 1-8 parameters
#define BSO_(a, b, c, d, e, f, g, h, ...) (0xFF & (1<<(a) | 1<<(b) | 1<<(c) | 1<<(d) | 1<<(e) | 1<<(f) | 1<<(g) | 1<<(h)))
#define BSO(...) BSO_(__VA_ARGS__, 8, 8, 8, 8, 8, 8, 8, 8)

// Macros to set, clear and flip multiple bits in registers
#define BITS_SET(x, ...) x |= BSO(__VA_ARGS__)
#define BITS_CLEAR(x, ...) x &= ~BSO(__VA_ARGS__)
#define BITS_SET_EX(x, ...) x = BSO(__VA_ARGS__)
#define BITS_FLIP(x, ...) x ^= BSO(__VA_ARGS__)

// Common defines
#define DIR_OUT 1
#define DIR_IN 0
#define LEVEL_HIGH 1
#define LEVEL_LOW 0
#define PULL_ENABLE 1
#define PULL_DISABLE 0
