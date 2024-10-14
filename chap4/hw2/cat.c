#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    int line_number = 1;
    int print_line_numbers = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        print_line_numbers = 1;
        argc--;
        argv++;
    }

    if (argc < 2) {
        fp = stdin;
    } else {
        for (int i = 1; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "Error: Cannot open file %s\n", argv[i]);
                continue;
            }

            while ((c = getc(fp)) != EOF) {
                if (print_line_numbers && c == '\n' && line_number > 1) {
                    printf("%d\t", line_number);
                }
                putchar(c);
                if (c == '\n') {
                    line_number++;
                }
            }
            fclose(fp);
        }
    }

    return 0;
}

