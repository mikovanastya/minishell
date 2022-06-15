#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd1 = open("./password", O_CREAT | O_WRONLY, 0755);

    printf( "fd1 is :: %d\n", fd1);
    write(fd1, "Tony?\n", strlen("Tony?\n"));

    int fd2 = dup(fd1);

    printf( "fd2 is :: %d\n" ,fd2);
    write(fd2, "Ezekiel?\n", strlen("Ezekiel?\n"));
    return 0;
}
