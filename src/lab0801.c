#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static const size_t FSZ = 100 * 1024 * 1024;
static const size_t RSZ = 40 * 1024 * 1024;

int
main(void)
{
        int fd;
        char *buf;
        char tn[] = "/var/tmp/21XXXXXX";
        off_t off;
        size_t len;

        if ((fd = mkstemp(tn)) < 0) {
                perror("mkstemp");
                exit(1);
        }

        (void) unlink(tn);

        if (ftruncate(fd, FSZ) != 0) {
                perror("ftruncate");
                exit(2);
        }

        if ((buf = malloc(RSZ)) == NULL) {
                perror("malloc");
                exit(3);
        }

        srand48(time(NULL));

        for (;;) {
                off = lrand48() % (RSZ / 1024);
                if (lrand48() % 73 == 0)
                        len = RSZ;
                else
                        len = ((lrand48() % 3) % 2) * 1024 + 1024;

                if (len > FSZ - off)
                        len = FSZ - off;

                if (lseek(fd, off, SEEK_SET) != off) {
                        perror("lseek");
                        exit(4);
                }

                (void) read(fd, buf, len);
        }

        /*NOTREACHED*/
        free(buf);
        (void) close(fd);

        return (0);
}
