#include "apue.h"
#include <fcntl.h>

char buf[] = "1234";

int main()
{
    int fd;
    if ((fd = open("exercise_3.6.file", O_RDWR | O_APPEND, FILE_MODE)) < 0)
    {
        err_sys("open error");
    }

    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        err_sys("lseek error");
    }

    if (write(fd, buf, 5) == -1)
    {
        err_sys("write error");
    }

    exit(0);
}