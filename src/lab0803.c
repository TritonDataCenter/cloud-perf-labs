#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



#define FILENAME        "data100m"
#define FILECHUNKS      100
#define BUFSZ   1024 * 1024



int
main(int argc, char **argv)
{
        void *buf;
        int fd, i;
 
        if ((buf = malloc(BUFSZ)) == NULL) {
                perror(NULL);
                exit(1);
        }
 
        if ((fd = open(FILENAME, O_CREAT | O_WRONLY | O_DSYNC)) == -1) {
                perror(NULL);
                exit(1);
        }

        for (;;) {
                for (i = 0; i != FILECHUNKS; i++) {
                        if (write(fd, buf, BUFSZ) == -1) {
                                perror(NULL);
                                exit(1);
                        }
                }

                if (lseek(fd, 0, SEEK_SET) == -1) {
                        perror(NULL);
                        exit(1);
                }
        }

        return (0); /* NOTREACHED */
}
