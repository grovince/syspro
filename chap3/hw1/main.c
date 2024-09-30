#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAX_LINES 100

char lines[MAX_LINES][MAXLINE];
int line_count = 0; 

int main() {
    while (line_count < MAX_LINES && fgets(lines[line_count], MAXLINE, stdin) != NULL) {
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0'; 
        line_count++;
    }

    for (int i = 0; i < line_count - 1; i++) {
        for (int j = i + 1; j < line_count; j++) {
            if (strlen(lines[i]) < strlen(lines[j])) {
                char temp[MAXLINE];
                copy(lines[i], temp);
                copy(lines[j], lines[i]);
                copy(temp, lines[j]);
            }
        }
    }

    for (int i = 0; i < line_count; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}

