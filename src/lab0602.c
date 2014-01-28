#include <sys/types.h>
#include <sys/processor.h>
#include <sys/procset.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *
a(void *arg __attribute__((__unused__)))
{
        const char *msg = "foo/bar/baz/quux/quuux/quuuux/quuuuuux/a";
        const char *a = msg;

        for (;;) {
                if (strchr(a, '/') == NULL)
                        a = msg;
                else
                        ++a;
        }

        /*NOTREACHED*/
        return (NULL);
}

int
main(void)
{
        uint_t i;
        pthread_t t[2];

        if (processor_bind(P_PID, getpid(), getcpuid(), NULL) != 0) {
                perror("processor_bind");
                exit(1);
        }

        for (i = 0; i < 2; i++) {
                if (pthread_create(&t[i], NULL, a, NULL) != 0) {
                        perror("pthread_create");
                        exit(2);
                }
        }

        for (i = 0; i < 2; i++)
                (void) pthread_join(t[i], NULL);

        return (0);
}
