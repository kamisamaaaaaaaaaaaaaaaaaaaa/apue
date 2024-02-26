#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096

int mydup2(int fd1, int fd2)
{
    if (fd1 == fd2)
        return fd2;

    struct cache_node
    {
        int fd;
        struct cache_node *next;
    } *head = (struct cache_node *)malloc(sizeof(struct cache_node));
    head->next = 0;

    int new_fd;
    while (1)
    {
        new_fd = dup(fd1);
        if (new_fd == fd2)
        {
            break;
        }
        else if (new_fd > fd2)
        {
            close(new_fd);
            close(fd2);
        }
        else
        {
            struct cache_node *temp_node = (struct cache_node *)malloc(sizeof(struct cache_node));
            temp_node->fd = new_fd;
            temp_node->next = head->next;
            head->next = temp_node;
        }
    }

    for (struct cache_node *cur = head, *ne = head->next; cur;)
    {
        if (cur != head)
        {
            close(cur->fd);
        }
        free(cur);

        cur = ne;
        if (cur)
        {
            ne = cur->next;
        }
    }

    return new_fd;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        err_sys("argv invalid");
    }

    int fd;
    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
    {
        err_sys("open invalid");
    }

    close(STDOUT_FILENO);
    mydup2(fd, STDOUT_FILENO);

    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if (write(STDOUT_FILENO, buf, n) != n)
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