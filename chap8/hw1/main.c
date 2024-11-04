#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s -e [VAR_NAME] | -u | -g | -i | -p\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 3) {
            char *env_value = getenv(argv[2]);
            if (env_value) {
                printf("Value of %s: %s\n", argv[2], env_value);
            } else {
                printf("Environment variable %s not found.\n", argv[2]);
            }
        } else {
            extern char **environ;
            for (char **env = environ; *env != 0; env++) {
                printf("%s\n", *env);
            }
        }
    } else if (strcmp(argv[1], "-u") == 0) {
        printf("My real user ID: %d\n", getuid());
        printf("My effective user ID: %d\n", geteuid());
    } else if (strcmp(argv[1], "-g") == 0) {
        printf("My real group ID: %d\n", getgid());
        printf("My effective group ID: %d\n", getegid());
    } else if (strcmp(argv[1], "-i") == 0) {
        printf("My process ID: %d\n", getpid());
    } else if (strcmp(argv[1], "-p") == 0) {
        printf("My parent process ID: %d\n", getppid());
    } else {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

