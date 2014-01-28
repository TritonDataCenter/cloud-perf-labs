/*
 * Hot slow CPU function, with 3-layer stack.
 * Eg, loop{ a()->b()->c() }, and c() spends ~50ms on-CPU.
 *
 * 12-Sep-2012	Brendan Gregg	Created this.
 */

#define SPIN_COUNT	20	/* modify as needed */

void
c()
{
	int i, j;
	for (i = 0; i < SPIN_COUNT; i++) {
		for (j = 0; j < 1000000; j++) { ; }
	}
}

void
b()
{
	c();
}

void
a()
{
	b();
}

int
main()
{
	for (;;) {
		a();
	}

	return 0;
}
