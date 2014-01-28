/*
 * No error checking: loop over trying to open a non-existant file.
 *
 * 12-Sep-2012	Brendan Gregg	Created this.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

const char *filename = "database7";

void
load_data()
{
	int fd;

	/* try, try again */
	while ((fd = open(filename, O_RDONLY)) < 0) { ; }

	printf("DB restored successfully\n");
	close(fd);
}

void
restore_db()
{
	load_data();
}

int
main()
{
	restore_db();

	return 0;
}
