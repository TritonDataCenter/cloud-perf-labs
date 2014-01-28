/*
 * Hot slow CPU function, with 3-layer stack.
 * Quasi-realistic function names.
 *
 * 12-Sep-2012	Brendan Gregg	Created this.
 */

#define SPIN_COUNT	20	/* modify as needed */

void
read_row()
{
	int i, j;
	for (i = 0; i < SPIN_COUNT; i++) {
		for (j = 0; j < 1000000; j++) { ; }
	}
}

void
table_scan()
{
	read_row();
}

void
do_query()
{
	table_scan();
}

int
main()
{
	for (;;) {
		do_query();
	}

	return 0;
}
