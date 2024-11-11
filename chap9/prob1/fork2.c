#include <stdlib.h>
#include <stdio.h>
int main() 
{
   int pid;
   pid = fork();
   if (pid ==0) { // child process
      printf("[Child] : Hello, world pid=%d\n", getpid());
   }
   else {   // parent process
      printf("[Parent] : Hello, world pid=%d\n", getpid());
   }
}

