#include "apue.h"
#include <errno.h>

#define CL_OPEN "open" /* client's request for server */

extern char errmsg[];  /* error message string to return to client */
extern int oflag;      /* open() flag: O_xxx ... */
extern char *pathname; /* of file to open() for client */
extern pid_t c_pid;

int cli_args(int, char **);
int handle_request(char *, int, int);
int csopen(char *name, int oflag);
