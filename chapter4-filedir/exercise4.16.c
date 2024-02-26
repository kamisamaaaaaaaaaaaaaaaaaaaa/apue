#include "apue.h"
#include <fcntl.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    char *dir_name = "test";

    size_t pathlen = 0;
    char *pathname = path_alloc(&pathlen);
    if (getcwd(pathname, pathlen) == NULL)
    {
        err_sys("getcwd error");
    }
    pathlen = strlen(pathname);

    size_t depth = 0;
    while (1)
    {
        if (mkdir(dir_name, 0777) == -1)
        {
            printf("depth: %ld pathlen: %ld\n", depth, pathlen);
            err_sys("mkdir error");
        }
        if (chdir(dir_name) == -1)
        {
            printf("depth: %ld pathlen: %ld\n", depth, pathlen);
            err_sys("chdir error");
        }
        ++depth;
        pathlen += strlen(dir_name) + 1;
    }

    exit(0);
}