#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define NLOOPS 1000
#define SIZE sizeof(long) /* size of shared memory area */

void MY_TELL_WAIT(void);
void MY_TELL_PARENT(pid_t pid);
void MY_WAIT_CHILD(void);
void MY_TELL_CHILD(pid_t pid);
void MY_WAIT_PARENT(void);
void MY_TELL_WAIT_DESTORY(void);

static int
update(long *ptr)
{
	return ((*ptr)++); /* return value before increment */
}

int main(void)
{
	int fd, i, counter;
	pid_t pid;
	void *area;

	if ((fd = open("/dev/zero", O_RDWR)) < 0)
		err_sys("open error");
	if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
					 fd, 0)) == MAP_FAILED)
		err_sys("mmap error");
	close(fd); /* can close /dev/zero now that it's mapped */

	MY_TELL_WAIT();

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid > 0)
	{ /* parent */
		for (i = 0; i < NLOOPS; i += 2)
		{
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);

			MY_TELL_CHILD(pid);
			MY_WAIT_CHILD();
		}
	}
	else
	{ /* child */
		for (i = 1; i < NLOOPS + 1; i += 2)
		{
			MY_WAIT_PARENT();

			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);

			MY_TELL_PARENT(getppid());
		}
	}

	MY_TELL_WAIT_DESTORY();

	exit(0);
}
