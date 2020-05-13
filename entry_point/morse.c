
#define UNIT_LENGTH 200

void on_for( int units ) {
	status_on();
	thr_delay(units * UNIT_LENGTH);
	status_off();
}

void dot() {
	on_for(1);
	thr_delay(1 * UNIT_LENGTH);
}

void dash() {
	on_for(3);
	thr_delay(1 * UNIT_LENGTH);
}

// Called after every char
void end_char() {
	thr_delay(2 * UNIT_LENGTH);
}

// Called after every word (after end_char())
void end_word() {
	thr_delay(4 * UNIT_LENGTH);
}
