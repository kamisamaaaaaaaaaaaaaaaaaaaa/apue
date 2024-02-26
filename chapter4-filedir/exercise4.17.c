#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        err_quit("usage: ./exercise4.17 [pathname]");
    }

    unlink(argv[1]);

    if (creat(argv[1], FILE_MODE) == -1)
    {
        err_sys("create error");
    }

    exit(0);
}