/*
 * Hot slow CPU function, with 3-layer stack, and wait time.
 * Quasi-realistic function names. Aiming for a 1:4 ratio of CPU:sleep.
 *
 * 12-Sep-2012	Brendan Gregg	Created this.
 */

#define SPIN_COUNT	4	/* modify as needed */
#define DELAY		50	/* ms */

void
match_field()
{
	int i, j;
	for (i = 0; i < SPIN_COUNT; i++) {
		for (j = 0; j < 1000000; j++) { ; }
	}
}

void
do_query()
{
	match_field();
}

void
wait_for_work()
{
	usleep(DELAY * 1000);
}

int
main()
{
	for (;;) {
		do_query();
		wait_for_work();
	}

	return 0;
}
