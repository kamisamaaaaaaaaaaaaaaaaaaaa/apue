#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 1073741824
char buff[BUFFSIZE];

static void
sig_alarm(int signo)
{
    printf("caught signal\n");
}

int main(void)
{
    if (signal_reli(SIGALRM, sig_alarm) < 0)
    {
        err_sys("signal error");
    };

    FILE *f = fopen("fwrite_signal_test.file", "w");
    alarm(1);
    if (fwrite(buff, sizeof(char), BUFFSIZE, f) != BUFFSIZE)
    {
        err_sys("fwrite error");
    };
}
