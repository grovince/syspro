#include <stdio.h>
#include <unistd.h>

int main()
{    
    printf("my pid : [%d] \n", getpid());
    printf("my ppid : [%d] \n", getppid());
}

