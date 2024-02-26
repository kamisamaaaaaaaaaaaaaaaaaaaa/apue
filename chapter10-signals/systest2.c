#include "apue.h"

extern int my_system(const char *cmdstring);

static void
sig_int(int signo)
{
	printf("caught SIGINT\n");
}

static void
sig_chld(int signo)
{
	printf("caught SIGCHLD\n");
}

int main(void)
{
	if (signal_reli(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	if (signal_reli(SIGCHLD, sig_chld) == SIG_ERR)
		err_sys("signal(SIGCHLD) error");
	if (my_system("/bin/ed") < 0)
		err_sys("system() error");
	exit(0);
}
