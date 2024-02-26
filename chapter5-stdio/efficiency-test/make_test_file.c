#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 516581760

char buf[BUFFSIZE];

int main()
{
    buf[BUFFSIZE - 1] = '\0';
    for (size_t i = 0; i < BUFFSIZE - 1; ++i)
    {
        buf[i] = 'a';
    }

    int fd;

    if ((fd = open("test.file", O_CREAT | O_WRONLY, FILE_MODE)) < 0)
    {
        err_sys("creat error");
    }

    if (write(fd, buf, BUFFSIZE) != BUFFSIZE)
    {
        err_sys("buf write error");
    }

    exit(0);
}