#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 6;
char buf[] = "a write to stdout \n";

int main(int argc, char **argv)
{
    int var;
    pid_t pid;

    var = 88;

    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
    {
        perror("write error");
    }

    printf("before fork \n"); // not flush stdout

    if ((pid = fork()) < 0)
    {   
        perror("fork error ");
    } 
    else if (pid == 0) // child
    {
        globvar++;
        var++;
    }
    else // parent
    {
        sleep(2); // 等待子进程先执行
    }

    printf("pid = %d, glob = %d, var = %d \n", getpid(), globvar, var);
    exit(0);
}