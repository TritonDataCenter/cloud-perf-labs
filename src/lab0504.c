/*
 * 1 byte sequential reads.
 *
 * 12-Sep-2012	Brendan Gregg	Created this.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

const char *filename = "data100m";

void
load_data()
{
	int fd;
	char buf[1];

	if ((fd = open(filename, O_RDONLY)) < 0) {
		perror("Can't open infile");
		printf("Please run \"dd if=/dev/zero of=data100m bs=1024k "
		    "count=100\" beforehand\n");
		exit(2);
	}

	while (read(fd, &buf, 1) > 0) { ; }

	(void) close(fd);
}

void
restore_db()
{
	load_data();
}

int
main()
{
	for (;;) {
		restore_db();
	}

	return 0;
}
