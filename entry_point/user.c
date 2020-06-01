#include <kyu.h>
#include <thread.h>
#include "orange_pi/gpio.h"

#include "retro_graphics.h"

static struct thread *user_thread;
static int count;

void user_init(int xx) {
    printf("*********************\nUser Entry Point\n\n");
    init_graphics(ASCII);
    // From here on, use retro_printf()
    // 
    Buffer* buffers[3];
    Coordinate coordinates[3];
    unsigned num_buffers = 0;

    Buffer* square = NEW(Buffer); // Asumming malloc returns zeroed memory
    square->rows = 200;
    square->columns = 400;
    square->layer = 4;
    Coordinate square_at = { .row = 30, .column = 6 };

    unsigned left_side = (400-180)/2;
    unsigned right_side = 400 - ((400-180)/2);
    for (unsigned row = 20;
         row < 180;
         row++
        ) {
        square->pixels[row][left_side].name = Red;
        square->pixels[row][right_side].name = Red;
    }
    for (unsigned col = left_side;
         col < right_side;
         col++
        ) {
        square->pixels[20][col].name = Blue;
        square->pixels[179][col].name = Blue;
    }

    buffers[num_buffers] = square;
    coordinates[num_buffers] = square_at;
    num_buffers++;

    Buffer* circle = NEW(Buffer); // Asumming malloc returns zeroed memory
    circle->rows = 201;
    circle->columns = 201;
    circle->layer = 6;
    Coordinate circle_at = { .row = 10, .column = 14 };

    circle->pixels[200][100].name = White;
    circle->pixels[195][130].name = White;
    circle->pixels[180][158].name = Green;
    circle->pixels[158][180].name = White;
    circle->pixels[130][195].name = White;
    circle->pixels[100][200].name = White;
    circle->pixels[70][195].name = White;
    circle->pixels[42][180].name = White;
    circle->pixels[20][158].name = White;
    circle->pixels[5][130].name = Cyan;
    circle->pixels[0][100].name = White;
    circle->pixels[5][70].name = White;
    circle->pixels[20][42].name = White;
    circle->pixels[42][20].name = Magenta;
    circle->pixels[70][5].name = White;
    circle->pixels[100][0].name = White;
    circle->pixels[130][5].name = White;
    circle->pixels[158][20].name = White;
    circle->pixels[180][42].name = White;
    circle->pixels[195][70].name = White;

    buffers[num_buffers] = circle;
    coordinates[num_buffers] = circle_at;
    num_buffers++;

    bool circle_on_top = true;

    #define MAXB 64
    char buf[MAXB];
    for ( ;; ) {
        retro_clear_text_no_update();
        retro_printf ( "\n"
                       "R to Reboot Pi.\n"
                       "T to cycle buffers/frames\n"
                       "Enter: "
                     );

        getline ( buf, MAXB );
        switch (buf[0]) {
        case '\0':
            break;

        case 'R':
            // Reboot the machine
            retro_printf ( "Rebooting\n" );
            reset_cpu ();            
            return;

        case 'T':
            update_frame(buffers, coordinates, num_buffers);

            // Swap which buffer is on top
            if (circle_on_top) {
                square->layer = 7;
                circle->layer = 2;
            }
            else {
                circle->layer = 4;
                square->layer = 1;
            }
            circle_on_top = !circle_on_top;
            break;

        default:
            break;
        }
    }
}
