#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

// 스택에 데이터를 푸시하는 함수
void push(struct node **top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

// 스택을 출력하는 함수
void print_stack(struct node *top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    struct node *current = top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *stack = NULL;
    char input[100];
    int value;

    while (1) {
        // 사용자 입력을 받는다
        fgets(input, sizeof(input), stdin);

        // "Print stack"을 입력하면 스택 출력
        if (strncmp(input, "Print stack", 11) == 0) {
            print_stack(stack);
			exit(0);
        }
        // 숫자 입력 시 스택에 푸시
        else if (sscanf(input, "%d", &value) == 1) {
            push(&stack, value);
        }
        // "exit"을 입력하면 프로그램 종료
        else if (strncmp(input, "exit", 4) == 0) {
            break;
        }
        else {
            printf("Invalid input\n");
        }
    }

    return 0;
}

