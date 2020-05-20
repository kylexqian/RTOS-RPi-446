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

Frame*
makeFrame(Buffer* buf, Coordinate at) {
    Frame* onto = NEW(Frame); // Assuming malloc returns zeroed memory
    return compositeOnto(buf, at, onto);
}

Frame*
compositeOnto(Buffer* buf, Coordinate at, Frame* onto) {
    for (unsigned int row=0;
         row < buf->rows;
         row++
        ) {
        for (unsigned int column=0;
             column < buf->columns;
             column++
            ) {
            onto->pixels[at.row+row][at.column+column]
                = buf->pixels[row][column];
        }
    }
    return onto;
}

Frame*
compositeLayers(Buffer* bufs[],
                Coordinate ats[],
                unsigned int numLayers,
                Frame* onto
               ) {

    // Simple O(n^2) selection sort to order buffer layers
    int mem = malloc(numLayers*( sizeof(unsigned char)
                                +sizeof(unsigned int)
                               )
                    );
    unsigned char   layer, maxLayer = 0, nextMaxLayer = 0;
    unsigned int    index, numSelectedIndices;
    // Cache buf->layer in layers to reduce distant memory accesses
    unsigned char*  layers  = (unsigned char*) mem;
    unsigned int*   sortedIndices = (unsigned int*) (layers+numLayers);
    for (index = 0; index < numLayers; index++) {
        layer = bufs[index]->layer;
        layers[index] = layer;
        if (layer > nextMaxLayer)
            nextMaxLayer = layer;
    }
    for (numSelectedIndices = 0; numSelectedIndices < numLayers; ) {
        maxLayer = nextMaxLayer;
        nextMaxLayer = 0;
        for (index = 0; index < numLayers; index++) {
            if (layers[index] == maxLayer) {
                sortedIndices[numSelectedIndices++] = index;
            }
            else if (layers[index] > nextMaxLayer) {
                nextMaxLayer = layers[index];
            }
        }
    }

    // Actually do the layering
    for (int i = numLayers-1; i >= 0; i--) {
        onto = compositeOnto(bufs[sortedIndices[i]],
                             ats[sortedIndices[i]],
                             onto
                            );
    }
    return onto;
}
