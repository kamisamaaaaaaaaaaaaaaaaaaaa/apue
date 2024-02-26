#include "apue.h"
#include <dirent.h>
#include <fcntl.h>

char fdstr[20];

int main(int argc, char *argv[])
{
    int flag;
    DIR *dir;
    struct dirent *entry;

    if (argc == 1)
    {
        if ((dir = opendir("/")) == NULL)
        {
            err_sys("opendir error");
        }
    }
    else if (argc == 2)
    {
        if ((dir = fdopendir(strtol(argv[1], NULL, 10))) == NULL)
        {
            err_sys("fdopendir error");
        }
    }

    if (fcntl(dirfd(dir), F_SETFD, 0) == -1)
    {
        err_sys("fcntl F_SETFD error");
    };

    if ((flag = fcntl(dirfd(dir), F_GETFD)) == -1)
    {
        err_sys("fcntl F_GETFD error");
    }

    if (flag == FD_CLOEXEC)
    {
        printf("FD_CLOEXEC set\n");
    }
    else
    {
        printf("FD_CLOEXEC not set\n");
    }

    if (argc == 2)
    {
        exit(0);
    }

    sprintf(fdstr, "%d", dirfd(dir));
    execlp("exercise8.7", "exercise8.7", fdstr, (char *)0);

    return 0;
}