#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 100

int main(int argc, char *argv[]) {
    int fd[2];  // 파이프: fd[0]은 읽기 끝, fd[1]은 쓰기 끝
    pid_t pid1, pid2;

    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(1);
    }

    // 파이프 생성
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // 첫 번째 자식 프로세스 (ls 실행)
    if ((pid1 = fork()) == 0) {
        // 쓰기 끝을 표준 출력에 연결
        close(fd[0]);  // 읽기 끝은 닫음
        if (dup2(fd[1], STDOUT_FILENO) == -1) {  // fd[1]을 표준 출력으로 변경
            perror("dup2");
            exit(1);
        }
        close(fd[1]);  // fd[1]은 더 이상 필요 없음

        // execvp를 사용해 ls 명령어 실행
        char *args1[] = {"ls", NULL};
        if (execvp(args1[0], args1) == -1) {
            perror("execvp");
            exit(1);
        }
    }

    // 두 번째 자식 프로세스 (wc 실행)
    if ((pid2 = fork()) == 0) {
        // 쓰기 끝을 표준 입력에 연결
        close(fd[1]);  // 쓰기 끝은 닫음
        if (dup2(fd[0], STDIN_FILENO) == -1) {  // fd[0]을 표준 입력으로 변경
            perror("dup2");
            exit(1);
        }
        close(fd[0]);  // fd[0]은 더 이상 필요 없음

        // execvp를 사용해 wc 명령어 실행
        char *args2[] = {"wc", "-l", NULL};  // -l 옵션을 사용하여 줄 수만 출력
        if (execvp(args2[0], args2) == -1) {
            perror("execvp");
            exit(1);
        }
    }

    // 부모 프로세스는 파이프의 양 끝을 닫고, 자식 프로세스들이 끝날 때까지 기다림
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);  // 첫 번째 자식 프로세스가 종료될 때까지 대기
    waitpid(pid2, NULL, 0);  // 두 번째 자식 프로세스가 종료될 때까지 대기

    return 0;
}

