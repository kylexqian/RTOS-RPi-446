#include "pixel.h"

void
printColorName(Color c) {
    switch (c.name) {
        case Black:
            printf("Black");
            break;
        case White:
            printf("White");
            break;
        case Red:
            printf("Red");
            break;
        case Green:
            printf("Green");
            break;
        case Blue:
            printf("Blue");
            break;
        case Yellow:
            printf("Yellow");
            break;
        case Magenta:
            printf("Magenta");
            break;
        case Cyan:
            printf("Cyan");
            break;
        default:
            printf("Unknown");
    }
}

void
printColorRGB(Color c) {
    printf("NB:%c R:%c G:%c B:%c",
           c.bits.NOTBLACK  ? 'x' : '_',
           c.bits.RED       ? 'x' : '_',
           c.bits.GREEN     ? 'x' : '_',
           c.bits.BLUE      ? 'x' : '_'
          );
}

void
printFrame(Frame* f) {
    printf("Frame at %#x\n", f);
    for (unsigned row=0; row < FRAME_ROWS; row++) {
        for (unsigned col=0; col < FRAME_COLUMNS; col++) {
            Color c = f->pixels[row][col];
            printf("(%d,%d): ", row, col);
            printColorRGB(c);
            printf(" ");
            printColorName(c);
            printf("\n");
        }
    }
}

void
asciiRenderFrame(Frame* f) {
    printf("%.*s\n", 2+FRAME_COLUMNS+2, LONG_HYPHEN_BAR);
    for (unsigned row=0; row < FRAME_ROWS; row++) {
        printf("| ");
        for (unsigned col=0; col < FRAME_COLUMNS; col++) {
            if (f->pixels[row][col].name > Black)
                printf("+");
            else
                printf(" ");
        }
        printf(" |\n");
    } 
    printf("%.*s\n", 2+FRAME_COLUMNS+2, LONG_HYPHEN_BAR);
}
