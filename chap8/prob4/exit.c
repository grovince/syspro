#include <stdio.h>
#include <stdio.h>
static void exit_handler1(void), exit_handler2(void);
int main(void) 
{
 if (atexit(exit_handler1) != 0)	
    perror("no exit_handler1");
 if (atexit(exit_handler2) != 0) 	
    perror("no exit_handler2");
 printf("main end \n");
exit(0);
}

static void exit_handler1(void)
{
   printf("1 exit\n");
}

static void exit_handler2(void)
{
  printf("2 exit\n");
}

