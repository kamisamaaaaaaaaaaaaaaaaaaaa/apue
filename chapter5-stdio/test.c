#include "apue.h"

int main()
{
    char buf[10];
    printf("123");
    fgets(buf, 10, stdin);
    if (stdin->_shortbuf == stdout->_shortbuf)
    {
        printf("true\n");
    }

    return 0;
}