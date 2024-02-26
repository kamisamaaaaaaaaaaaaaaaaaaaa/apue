#include "opend.h"
#include <fcntl.h>

#define BUFFSIZE 8192

char errmsg[MAXLINE];
int oflag;
char *pathname;

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2)
    {
        err_quit("usage：./a.out pathname");
    }

    TELL_WAIT();
    /* open the file */
    if ((fd = csopen(argv[1], O_RDONLY)) < 0)
    {
        err_sys("csopen error");
    } /* csopen() prints error from server */

    for (;;)
    {
        /* and cat to stdout */
        printf("parent offset is %ld\n", lseek(fd, 0, SEEK_CUR));
        TELL_CHILD(c_pid);
        WAIT_CHILD();
    }

    close(fd);

    exit(0);
}
