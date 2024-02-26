#include "apue.h"
#include <fcntl.h>

char buf[16384];

int main(void)
{
    buf[16384] = '\0';
    for (size_t i = 0; i < 16384; ++i)
    {
        buf[i] = 'a';
    }

    int fd;

    if ((fd = creat("file.nohole", FILE_MODE)) < 0)
        err_sys("creat error");

    if (write(fd, buf, 16384) != 16384)
        err_sys("buf1 write error");

    exit(0);
}
