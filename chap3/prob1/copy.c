#include <stdio.h>

void copy(char from[], char to[]){
   int j;
   j = 0;
   while((to[j] = from[j]) != '\0')
     ++j;
}

