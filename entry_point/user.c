#include <kyu.h>
#include <thread.h>
#include "morse.h"

static struct thread *user_thread;
static int count;

#define true 1
#define false 0

void
h() {
	printf("h ");
	dot();
	dot();
	dot();
	dot();
	end_char();
}

void
e() {
	printf("e ");
	dot();
	end_char();
}

void
l() {
	printf("l ");
	dot();
	dash();
	dot();
	dot();
	end_char();
}

void
o() {
	printf("o ");
	dash();
	dash();
	dash();
	end_char();
}

void
w() {
	printf("w ");
	dot();
	dash();
	dash();
	end_char();
}

void
r() {
	printf("r ");
	dot();
	dash();
	dot();
	end_char();
}

void
d() {
	printf("d ");
	dash();
	dot();
	dot();
	end_char();
}

void
user_init ( int xx )
{
	gpio_led_init ();
	while (true) {
		h();e();l();l();o();
		printf("  ");
		end_word();

		w();o();r();l();d();
		printf("\n");
		end_word();

		end_word();
	}
}
