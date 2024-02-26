#include "opend.h"
#include <sys/uio.h> /* struct iovec */

pid_t c_pid;
pid_t p_pid;

/*
 * Open the file by sending the "name" and "oflag" to the
 * connection server and reading a file descriptor back.
 */
int csopen(char *name, int oflag)
{
	int len;
	char buf[10];
	struct iovec iov[3];
	static int fd[2] = {-1, -1};
	p_pid = getpid();

	if (fd[0] < 0)
	{ /* fork/exec our open server first time */
		if (fd_pipe(fd) < 0)
		{
			err_ret("fd_pipe error");
			return (-1);
		}
		if ((c_pid = fork()) < 0)
		{
			err_ret("fork error");
			return (-1);
		}
		else if (c_pid == 0)
		{ /* child */
			close(fd[0]);

			int nread;
			char buf[MAXLINE];
			int newfd;

			if ((nread = read(fd[1], buf, MAXLINE)) < 0)
				err_sys("read error on stream pipe");

			newfd = handle_request(buf, nread, fd[1]);

			for (off_t i = 1; i <= 5; ++i)
			{
				WAIT_PARENT();
				printf("child set offset: %ld\n", lseek(newfd, i, SEEK_SET));
				TELL_PARENT(p_pid);
			}

			_exit(0);
		}

		close(fd[1]); /* parent */
	}
	sprintf(buf, " %d", oflag);	   /* oflag to ascii */
	iov[0].iov_base = CL_OPEN " "; /* string concatenation */
	iov[0].iov_len = strlen(CL_OPEN) + 1;
	iov[1].iov_base = name;
	iov[1].iov_len = strlen(name);
	iov[2].iov_base = buf;
	iov[2].iov_len = strlen(buf) + 1; /* +1 for null at end of buf */
	len = iov[0].iov_len + iov[1].iov_len + iov[2].iov_len;
	if (writev(fd[0], &iov[0], 3) != len)
	{
		err_ret("writev error");
		return (-1);
	}

	/* read descriptor, returned errors handled by write() */
	return (recv_fd(fd[0], write));
}
