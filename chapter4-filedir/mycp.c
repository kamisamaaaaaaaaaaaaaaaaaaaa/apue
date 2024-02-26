#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096
char buff[BUFFSIZE];

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        err_quit("usage: ./mycp [filename1] [filename2]");
    }

    int fd1;
    if ((fd1 = open(argv[1], O_RDONLY)) == -1)
    {
        err_sys("open source error");
    }

    struct stat file_stat;
    if (fstat(fd1, &file_stat) == -1)
    {
        err_sys("fstat error");
    }

    int fd2;
    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT, file_stat.st_mode)) == -1)
    {
        err_sys("open target error");
    }

    int n;
    int cnt, start;
    while ((n = read(fd1, buff, BUFFSIZE)) > 0)
    {
        cnt = start = 0;
        for (int i = 0; i < n; ++i)
        {
            if (buff[i] == '\0')
            {
                if (write(fd2, buff + start, i - start) != i - start)
                {
                    err_sys("write error");
                }
                for (; i < n && buff[i] == '\0'; ++i, ++cnt)
                    ;

                if (lseek(fd2, cnt, SEEK_CUR) == -1)
                {
                    err_sys("lseek error");
                }
                cnt = 0, start = i;
                --i;
            }
        }

        if (write(fd2, buff + start, n - start) != n - start)
        {
            err_sys("write error");
        }
    }

    if (n < 0)
    {
        err_sys("read error");
    }

    exit(0);
}