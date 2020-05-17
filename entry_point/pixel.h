#pragma once
/*\
 * 3-bit color with redundant Black/White bit (ones-place bit)
 * 
 * Makes:
 *  black 0  0x0
 *  White 15 0xF
 *
 * Preliminary Black/White display can simply read (C > 0)
 * Full 3-bit color display can ignore LSB in RGB field mask
\*/

typedef enum ColorName {
    Black   = 0b0000, // ___ _
    White   = 0b1111, // RGB x
    Red     = 0b1001, // R__ x
    Green   = 0b0101, // _G_ x
    Blue    = 0b0011, // __B x
    Yellow  = 0b1101, // RG_ x
    Magenta = 0b1011, // R_B x
    Cyan    = 0b0111, // _GB x
} ColorName;
typedef struct ColorBits {
    unsigned int NOTBLACK:  1;
    unsigned int BLUE    :  1;
    unsigned int GREEN   :  1;
    unsigned int RED     :  1;
} ColorBits;
typedef union Color {
    ColorName name;
    ColorBits bits;
} Color;

void
printColor(Color);

#define FRAME_ROWS    2
#define FRAME_COLUMNS 4
typedef struct Frame {
    Color pixels[FRAME_ROWS][FRAME_COLUMNS];
} Frame;

void
printFrame(Frame*);
