#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define NLOOPS 1000
#define SIZE sizeof(long) /* size of shared memory area */

static int
update(long *ptr)
{
	return ((*ptr)++); /* return value before increment */
}

int main(void)
{
	int shmid;
	int i, counter;
	pid_t pid;

	if ((shmid = shmget(IPC_PRIVATE, SIZE, O_CREAT | 0600)) == -1)
	{
		err_sys("shmget error");
	}

	void *area;
	if ((long)(area = shmat(shmid, NULL, 0)) == -1)
	{
		err_sys("parent shmat error");
	}

	TELL_WAIT();

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid > 0)
	{ /* parent */

		// void *area;
		// if ((long)(area = shmat(shmid, NULL, 0)) == -1)
		// {
		// 	err_sys("parent shmat error");
		// }

		for (i = 0; i < NLOOPS; i += 2)
		{
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);

			TELL_CHILD(pid);
			WAIT_CHILD();
		}
		// if (shmdt(area) == -1)
		// {
		// 	err_sys("parent shmdt error");
		// }
	}
	else
	{ /* child */
		// void *area;
		// if ((long)(area = shmat(shmid, NULL, 0)) == -1)
		// {
		// 	err_sys("child shmat error");
		// }
		for (i = 1; i < NLOOPS + 1; i += 2)
		{
			WAIT_PARENT();

			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);

			TELL_PARENT(getppid());
		}
		// if (shmdt(area) == -1)
		// {
		// 	err_sys("child shmdt error");
		// }
		_exit(0);
	}

	wait(NULL);
	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		err_sys("shmctl error");
	}

	exit(0);
}
