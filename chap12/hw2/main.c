#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 100

int main() {
    int fd1[2], fd2[2];
    pid_t pid1, pid2;
    char message[MAXLINE], line[MAXLINE];
    
    printf("parent process start\n");

    pipe(fd1);
    pipe(fd2);

    if ((pid1 = fork()) == 0) {
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);

        printf("input string: ");
        fgets(message, MAXLINE, stdin);
        message[strcspn(message, "\n")] = 0;

        write(fd1[1], message, strlen(message) + 1);

        close(fd1[1]);
        exit(0);
    }

    if ((pid2 = fork()) == 0) {
        close(fd1[1]);
        close(fd2[0]);

        int n = read(fd1[0], line, MAXLINE);
        line[n] = '\0';

        for (int i = 0; line[i]; i++) {
            line[i] = toupper(line[i]);
        }

        write(fd2[1], line, strlen(line) + 1);

        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[1]);

    int n = read(fd2[0], line, MAXLINE);
    line[n] = '\0';

    printf("%s\n", line);

    close(fd2[0]);
    wait(NULL);
    wait(NULL);

    return 0;
}
