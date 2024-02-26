#include <stdio.h>
#include <stdlib.h>
#include "apue.h"

void writeNum(int num)
{
    FILE *f = fopen("tell_wait_test.file", "w");
    fprintf(f, "%d\n", num);
    printf("process is %d writing %d\n", getpid(), num);
    fclose(f);
}

int main()
{
    int cur = 0;

    pid_t pid;
    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        cur = 1;
        while (1)
        {
            TELL_WAIT();
            WAIT_PARENT();

            writeNum(cur);
            cur += 2;
            TELL_PARENT(getppid());
        }

        _exit(0);
    }

    while (1)
    {
        writeNum(cur);
        cur += 2;
        TELL_CHILD(pid);

        TELL_WAIT();
        WAIT_CHILD();
    }

    return 0;
}