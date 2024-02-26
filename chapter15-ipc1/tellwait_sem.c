#include "apue.h"
#include <sys/sem.h>

static int sem_id;
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void MY_TELL_WAIT(void)
{
    if ((sem_id = semget(IPC_PRIVATE, 2, IPC_CREAT | 0600)) == -1)
    {
        err_sys("semget error");
    }

    union semun arg;
    arg.val = 0;
    if (semctl(sem_id, 0, SETVAL, arg) == -1)
    {
        err_sys("semctl error");
    }
    if (semctl(sem_id, 1, SETVAL, arg) == -1)
    {
        err_sys("semctl error");
    }
}

void MY_TELL_PARENT(pid_t pid)
{
    struct sembuf semoparray[1];
    semoparray[0].sem_op = 1;
    semoparray[0].sem_num = 0;
    semoparray[0].sem_flg = SEM_UNDO;

    if (semop(sem_id, semoparray, 1) == -1)
    {
        err_sys("semop error");
    }
}

void MY_WAIT_CHILD(void)
{
    struct sembuf semoparray[1];
    semoparray[0].sem_op = -1;
    semoparray[0].sem_num = 0;
    semoparray[0].sem_flg = SEM_UNDO;

    if (semop(sem_id, semoparray, 1) == -1)
    {
        err_sys("semop error");
    }
}

void MY_TELL_CHILD(pid_t pid)
{
    struct sembuf semoparray[1];
    semoparray[0].sem_op = 1;
    semoparray[0].sem_num = 1;
    semoparray[0].sem_flg = SEM_UNDO;

    if (semop(sem_id, semoparray, 1) == -1)
    {
        err_sys("semop error");
    }
}

void MY_WAIT_PARENT(void)
{
    struct sembuf semoparray[1];
    semoparray[0].sem_op = -1;
    semoparray[0].sem_num = 1;
    semoparray[0].sem_flg = SEM_UNDO;

    if (semop(sem_id, semoparray, 1) == -1)
    {
        err_sys("semop error");
    }
}

void MY_TELL_WAIT_DESTORY(void)
{
    semctl(sem_id, 0, IPC_RMID);
}
