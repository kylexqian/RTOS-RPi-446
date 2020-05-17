#include <kyu.h>
#include <thread.h>
#include "pixel.h"

static struct thread *user_thread;
static int count;

void user_init(int xx) {
    printf("*********************\nUser Entry Point\n\n");

    Frame* frame = (Frame*) malloc(sizeof(Frame));
    printFrame(frame);
    asciiRenderFrame(frame);

    frame->pixels[1][2].name = Blue;
    frame->pixels[0][3].name = Red;
    frame->pixels[1][1].name = Green;
    frame->pixels[0][0].name = Cyan;
    printFrame(frame);
    asciiRenderFrame(frame);

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
 

