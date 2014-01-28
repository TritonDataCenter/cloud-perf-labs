#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

void
c(void)
{
        sigset_t ss;

        (void) sigfillset(&ss);
        (void) sigdelset(&ss, SIGINT);
        (void) sigsuspend(&ss);
}

void
b(void)
{
        c();
}

void
a(void)
{
        b();
}

int
main(void)
{
        a();
        return (0);
}
