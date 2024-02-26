#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 100

static void
sig_handler(int signo)
{
    printf("caught signal\n");
}

int main(void)
{
    int n, w_n;
    char buf[BUFFSIZE];

    if (signal_intr(SIGXFSZ, sig_handler) < 0)
    {
        err_sys("signal error");
    }

    int fd;
    if ((fd = open("sigfxz_test.file", O_WRONLY | O_CREAT | O_TRUNC)) < 0)
    {
        err_sys("open error");
    }

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if ((w_n = write(fd, buf, n)) != n)
        {
            printf("write number: %d\n", w_n);
            write(fd, buf, n);
            err_sys("write error");
        }

    if (n < 0)
        err_sys("read error");

    exit(0);
}
