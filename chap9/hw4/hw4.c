#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

// 명령어를 실행하는 함수
void execute_command(char *cmdline) {
    char *args[MAX_ARGS];  // 명령어 인수 배열
    int background = 0;  // 후면 실행 여부
    int i = 0;

    // 명령어 끝에 &가 있으면 후면 실행으로 설정
    int len = strlen(cmdline);
    if (cmdline[len - 1] == '&') {
        background = 1;
        cmdline[len - 1] = '\0';  // '&' 제거
    }

    // 공백을 기준으로 명령어와 인수 분리
    char *token = strtok(cmdline, " ");
    while (token != NULL) {
        args[i] = token;  // 인수 배열에 저장
        i++;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;  // execvp()에 전달하려면 배열의 마지막에 NULL을 넣어야 함

    pid_t pid = fork();  // 자식 프로세스 생성

    if (pid == 0) {  // 자식 프로세스에서 명령어 실행
        printf("[%d] Child process start\n", getpid());  // 자식 프로세스 시작 메시지
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
            exit(1);
        }
        printf("[%d] Child process end\n", getpid());  // 자식 프로세스 종료 메시지
    } else if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else {  // 부모 프로세스
        printf("[%d] Parent process start\n", getpid());  // 부모 프로세스 시작 메시지
        if (!background) {
            // 백그라운드 실행이 아니면 자식 프로세스가 종료될 때까지 기다림
            waitpid(pid, NULL, 0);
        }
        printf("[%d] Parent process end\n", getpid());  // 부모 프로세스 종료 메시지
    }
}

int main() {
    char cmdline[MAX_CMD_LEN];  // 명령어 입력을 저장할 배열

    while (1) {
        printf("Pls input cmd : ");  // 프롬프트 출력
        if (fgets(cmdline, MAX_CMD_LEN, stdin) == NULL) {
            perror("fgets failed");
            exit(1);
        }

        // 개행 문자 제거
        cmdline[strcspn(cmdline, "\n")] = 0;

        // 빈 명령어는 무시
        if (strlen(cmdline) == 0) {
            continue;
        }

        // 명령어 실행
        execute_command(cmdline);
    }

    return 0;
}

