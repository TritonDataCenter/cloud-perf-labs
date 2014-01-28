/*
 * 2 Hot slow CPU functions, with a ratio between them.
 * Eg, a()->b()->c()->d(), and, a()->b()->c()->e(). d:e ratio 1:2.
 */

#define SPIN_COUNT	5	/* modify as needed */

void
e()
{
	int i, j;
	for (i = 0; i < 2 * SPIN_COUNT; i++) {
		for (j = 0; j < 1000000; j++) { ; }
	}
}

void
d()
{
	int i, j;
	for (i = 0; i < SPIN_COUNT; i++) {
		for (j = 0; j < 1000000; j++) { ; }
	}
}

void
c()
{
	d();
	e();
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
