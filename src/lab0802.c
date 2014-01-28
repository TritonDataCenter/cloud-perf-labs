/*
 * crazy mmap(). random 4k reads of "data100m" via 4k
 * mmap()/munmap() cycles.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define	FILENAME	"data100m"

char the_awesome_buffer[4096];
long pagesize;

int
getdatafile()
{
	int fd;
	
	fd = open(FILENAME, O_RDWR | O_CREAT, 0644);
	return (fd);
}

void
fetchpage(int fd, off_t offset)
{
	char *map;

	offset &= ~((unsigned int)(pagesize - 1));

	/* mmap */
	map = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
	if (map == MAP_FAILED)
		err(1, "could not mmap file, oh my");
	/* read page */
	memcpy(the_awesome_buffer, map, 4096);
	/* munmap */
	if (munmap(map, 4096) == -1)
		err(1, "could not munmap file, oh my");
}

void
workloop(int fd, off_t min, off_t max)
{
	off_t offs;

	max -= 4096;
	if (max < 0)
		errx(1, "file should be at least 4k");

	offs = random() % (max - min) + min;

	fetchpage(fd, offs);
}

size_t
rangefinder(int fd)
{
	struct stat st;

	if (fstat(fd, &st) == -1)
		err(1, "could not stat %s", FILENAME);

	return (st.st_size);
}

int
main(int argc, char **argv)
{
	int fd = getdatafile();
	size_t max = rangefinder(fd);

	pagesize = sysconf(_SC_PAGESIZE);
	srandom(time(NULL));

	for (;;)
		workloop(fd, 0, max);
}
