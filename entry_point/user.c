#include <kyu.h>
#include <thread.h>
#include "pixel.h"

static struct thread *user_thread;
static int count;

void user_init(int xx) {
    printf("*********************\nUser Entry Point\n\n");

    Frame* frame = NEW(Frame);
    frame->pixels[1][2].name = Blue;
    frame->pixels[0][3].name = Red;
    frame->pixels[1][1].name = Green;
    frame->pixels[0][0].name = Cyan;
    asciiRenderFrame(frame);

    Frame* frame2 = NEW(Frame);
    frame2->pixels[0][0].name = Magenta;
    frame2->pixels[0][1].name = Magenta;
    frame2->pixels[0][2].name = Magenta;
    frame2->pixels[0][3].name = Magenta;
    asciiRenderFrame(frame2);

    #define MAXB    64
    char buf[MAXB];
    for ( ;; ) {
        printf ( "R to Reboot: " );
        getline ( buf, MAXB );
        if ( ! buf[0] )
            continue;

        if ( buf[0] == 'R' ) {
            /* Reboot the machine */
            printf ( "Rebooting\n" );
            reset_cpu ();
        }
    }
}
 

