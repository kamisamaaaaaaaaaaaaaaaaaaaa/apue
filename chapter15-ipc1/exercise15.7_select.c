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

    fd_set readfds, writefds, execptfds;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&execptfds);

    // FD_SET(fd[0], &readfds);
    // FD_SET(fd[0], &writefds);
    // FD_SET(fd[0], &execptfds);

    FD_SET(fd[1], &execptfds);
    FD_SET(fd[1], &writefds);
    FD_SET(fd[1], &readfds);

    if (select(FD_SETSIZE, &readfds, &writefds, &execptfds, NULL) == -1)
    {
        perror("select error");
    }

    // if (FD_ISSET(fd[0], &readfds))
    // {
    //     printf("pipe readfd readable\n");
    // }
    // if (FD_ISSET(fd[0], &writefds))
    // {
    //     printf("pipe readfd writable\n");
    // }
    // if (FD_ISSET(fd[0], &execptfds))
    // {
    //     printf("pipe readfd exception\n");
    // }

    if (FD_ISSET(fd[1], &readfds))
    {
        printf("pipe writefd readable\n");
    }
    if (FD_ISSET(fd[1], &writefds))
    {
        printf("pipe writefd writable\n");
    }
    if (FD_ISSET(fd[1], &execptfds))
    {
        printf("pipe writefd exception\n");
    }

    return 0;
}