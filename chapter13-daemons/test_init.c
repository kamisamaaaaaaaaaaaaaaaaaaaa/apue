#include <unistd.h>

void daemonize(const char *cmd);

int main()
{
    daemonize(NULL);
    pause();
    return 0;
}