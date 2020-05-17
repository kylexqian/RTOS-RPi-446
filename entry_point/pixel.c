#include "pixel.h"

#define MAX_LENGTH_COLOR_PRINT_STRING "NB:_ R:_ G:_ B:_ => Magenta0"
#define MAX_LENGTH_OF_COLOR_PRINT_STRING sizeof(MAX_LENGTH_COLOR_PRINT_STRING)
void
printColor(Color c) {
    char bufStart[MAX_LENGTH_OF_COLOR_PRINT_STRING];
    char* buf = bufStart;
    buf += sprintf(buf, "NB:%c ", c.bits.NOTBLACK ? 'x' : '_');
    buf += sprintf(buf, "R:%c ", c.bits.RED? 'x' : '_');
    buf += sprintf(buf, "G:%c ", c.bits.GREEN? 'x' : '_');
    buf += sprintf(buf, "B:%c => ", c.bits.BLUE? 'x' : '_');

    char cName[sizeof("Magenta")];
    switch (c.name) {
        case Black:
            buf += sprintf(buf, "Black");
            break;
        case White:
            buf += sprintf(buf, "White");
            break;
        case Red:
            buf += sprintf(buf, "Red");
            break;
        case Green:
            buf += sprintf(buf, "Green");
            break;
        case Blue:
            buf += sprintf(buf, "Blue");
            break;
        case Yellow:
            buf += sprintf(buf, "Yellow");
            break;
        case Magenta:
            buf += sprintf(buf, "Magenta");
            break;
        case Cyan:
            buf += sprintf(buf, "Cyan");
            break;
        default:
            buf += sprintf(buf, "Unknown");
    }
    printf(bufStart);
}

void
printFrame(Frame* f) {
    printf("Frame at %#x\n", f);
    for (unsigned row=0; row < FRAME_ROWS; row++) {
        for (unsigned col=0; col < FRAME_COLUMNS; col++) {
            printf("(%d,%d): ", row, col);
            printColor(f->pixels[row][col]);
            printf("\n");
        }
    }
}
