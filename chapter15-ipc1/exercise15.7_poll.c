#include <sys/select.h>
#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe error");
    }

    // close(fd[1]);
    close(fd[0]);

    struct pollfd fdarray[1];
    fdarray[0].events = POLLIN | POLLPRI | POLLOUT | POLLERR | POLLHUP | POLLNVAL;
    fdarray[0].fd = fd[1];

    if (poll(fdarray, 1, -1) == -1)
    {
        perror("poll error");
    }

    if (fdarray[0].revents & POLLIN)
    {
        printf("POLLIN OCCUR\n");
    }
    if (fdarray[0].revents & POLLPRI)
    {
        printf("POLLPRI OCCUR\n");
    }
    if (fdarray[0].revents & POLLOUT)
    {
        printf("POLLOUT OCCUR\n");
    }
    if (fdarray[0].revents & POLLERR)
    {
        printf("POLLERR OCCUR\n");
    }
    if (fdarray[0].revents & POLLHUP)
    {
        printf("POLLHUP OCCUR\n");
    }
    if (fdarray[0].revents & POLLNVAL)
    {
        printf("POLLNVAL OCCUR\n");
    }

    return 0;
}