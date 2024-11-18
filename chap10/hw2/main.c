#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

// 큐에 데이터를 추가하는 함수
void addq(struct node **head, struct node **tail, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    if (*tail == NULL) {  // 큐가 비어있는 경우
        *head = *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

// 큐를 출력하는 함수
void print_queue(struct node *head) {
    if (head == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    struct node *current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *head = NULL, *tail = NULL;
    char input[100];
    int value;

    while (1) {
        // 사용자 입력을 받는다
        fgets(input, sizeof(input), stdin);

        // "x" 입력 시 큐 내용 출력하고 종료
        if (strncmp(input, "x", 1) == 0) {
            printf("Print queue\n");
            print_queue(head);
            break;
        }
        
        // 숫자 입력 시 큐에 추가
        if (sscanf(input, "%d", &value) == 1) {
            addq(&head, &tail, value);
        } 
        // 잘못된 입력에 대한 처리
        else {
            printf("Invalid input\n");
        }
    }

    return 0;
}

