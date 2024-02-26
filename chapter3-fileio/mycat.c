#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 1

void setfd(int fd, int opt)
{
	int oldopts = fcntl(fd, F_GETFL);
	if (fcntl(fd, F_SETFL, oldopts | opt) == -1)
	{
		err_sys("fcntl error");
	}
}

int main(void)
{
	int n;
	char buf[BUFFSIZE];

	// setfd(STDOUT_FILENO, O_SYNC);

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	// if (fsync(STDOUT_FILENO) == -1)
	// {
	// 	err_sys("fdatasync error");
	// }

	exit(0);
}
