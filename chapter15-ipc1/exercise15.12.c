#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int id;
    for (int i = 0; i < 5; ++i)
    {
        if ((id = msgget(i, IPC_CREAT)) == -1)
        {
            perror("msgget error");
        }
        printf("id of msgq %d is %d\n", i, id);
        if (msgctl(id, IPC_RMID, NULL) == -1)
        {
            perror("msgctl error");
        }
    }

    struct
    {
        long mtype;
        char mtext[512];
    } msg;
    msg.mtype = 1;
    memcpy(msg.mtext, "hello", strlen("hello") + 1);

    for (int i = 0; i < 5; ++i)
    {
        if ((id = msgget(IPC_PRIVATE, IPC_CREAT | 0200)) == -1)
        {
            perror("msgget error");
        }
        if (msgsnd(id, &msg, 512, 0) == -1)
        {
            perror("msgsnd error");
        }
    }

    return 0;
}