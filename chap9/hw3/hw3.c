#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024

// 명령어 실행 함수
void execute_cmd(char *cmd) {
    char *args[MAX_LINE / 2 + 1];
    int i = 0;
    
    // 공백을 기준으로 명령어 인자 분리
    char *token = strtok(cmd, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // 인자 끝

    // 자식 프로세스를 생성하여 명령어 실행
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);  // 명령어 실행
        perror("Execution failed");  // 실행 실패 시 오류 출력
        exit(1);
    } else {
        wait(NULL);  // 부모는 자식 프로세스가 끝날 때까지 기다림
    }
}

int main() {
    char line[MAX_LINE];

    while (1) {
        printf("[shell] ");
        if (!fgets(line, MAX_LINE, stdin)) break;  // 입력 받기
        line[strcspn(line, "\n")] = 0;  // 입력에서 개행 제거

        if (strlen(line) == 0) continue;  // 빈 입력은 무시

        // 명령어가 ';'로 구분된 경우
        if (strchr(line, ';')) {
            char *cmd = strtok(line, ";");
            while (cmd != NULL) {
                execute_cmd(cmd);  // 명령어 실행
                cmd = strtok(NULL, ";");
            }
        }
        // 명령어가 '&'로 후면 실행인 경우
        else if (strchr(line, '&')) {
            line[strcspn(line, "&")] = 0;  // '&' 제거
            if (fork() == 0) {
                execute_cmd(line);  // 후면 실행
                exit(0);
            }
        }
        // 일반 명령어 실행
        else {
            execute_cmd(line);
        }
    }

    return 0;
}

