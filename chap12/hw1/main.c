#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); 

    if (pid < 0) { 
        perror("fork failed");
        exit(1);
    }
    
    if (pid > 0) {
        wait(NULL); 
        printf("Send: [100] Hello from PID 100\n");
    } else {
        printf("Recv: [1101] Hello from PID 100\n"); 
    }

    return 0;
}

