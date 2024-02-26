#include "apue.h"
#include <semaphore.h>
#include <fcntl.h>

sem_t *p_sem, *c_sem;

void MY_TELL_WAIT(void)
{
    if ((p_sem = sem_open("/parent", O_CREAT | O_EXCL, S_IRWXU, 0)) == SEM_FAILED)
    {
        err_sys("p_sem create failed");
    }
    if ((c_sem = sem_open("/child", O_CREAT | O_EXCL, S_IRWXU, 0)) == SEM_FAILED)
    {
        err_sys("c_sem create failed");
    }
}

void MY_TELL_PARENT(pid_t pid)
{
    sem_post(p_sem);
}

void MY_WAIT_CHILD(void)
{
    sem_wait(p_sem);
}

void MY_TELL_CHILD(pid_t pid)
{
    sem_post(c_sem);
}

void MY_WAIT_PARENT(void)
{
    sem_wait(c_sem);
}

void MY_TELL_WAIT_DESTORY(void)
{
    sem_unlink("/parent");
    sem_unlink("/child");
}
