#include <kyu.h>
#include <thread.h>
#include "pixel.h"

static struct thread *user_thread;
static int count;

void user_init(int xx) {
    printf("*********************\nUser Entry Point\n\n");

    Frame* frame = (Frame*) malloc(sizeof(Frame));
    printFrame(frame);

    frame->pixels[1][2].name = Blue;
    frame->pixels[0][3].name = Red;
    frame->pixels[1][1].name = Green;
    frame->pixels[0][0].name = Cyan;
    printFrame(frame);
   
    gpio_led_init ();
    while (true) {
        ;
    }
}
