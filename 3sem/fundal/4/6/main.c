

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Node {
    char* data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(char* data) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void LIST_NodePush(Node* node, Node** tail) {
    if (*tail == NULL) {
        *tail = node;
        return;
    }

    Node* cur = *tail;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    node->prev = cur;
    *tail = node;
}

Node* STACK_NodePop(Node** top) {
    Node* result = *top;
    if (*top != NULL && (*top)->prev != NULL) {
        *top = (*top)->prev;
        (*top)->next = NULL;
    }
    return result;
}

Node* QUEUE_NodeDequeue(Node** head) {
    Node* result = *head;
    if (*head == NULL) return NULL;
    if ((*head)->next != NULL) {
        *head = (*head)->next;
        (*head)->prev = NULL;
    }  else {
        *head = NULL;
    }
    result->prev = NULL;
    result->next = NULL;
    return result;
}

int main(int argc, char* argv[]) {
    FILE* file;
    if (argc < 2 || !(file = fopen(argv[1], "w"))) {
        exit(-1);
    }
    char str[250];
    int n, i = 1;
    scanf("%d", &n);
    scanf("%s", str);
    Node* head = NULL;
    Node* tailOrTop = NULL;

    int answ;
    while (strcmp(str, "STOP") != 0) {
//        printf("%s\n", str);
        char *data = malloc(sizeof(char) * (strlen(str) + 1));
        strcpy(data, str);
        Node* node = createNode(data);
        if (head == NULL) head = node;
        LIST_NodePush(node, &tailOrTop);
        if (i == n) {
            printf("Remove N/2? (1/0): ");
            scanf("%d", &answ);
            printf("\n");
            if (answ == 1) {
                for (int j = 0; j < n / 2; ++j) {
                    Node* remove = STACK_NodePop(&tailOrTop);
                    free(remove->data);
                    free(remove);
                }
            }
            Node* dequeue = QUEUE_NodeDequeue(&head);
            while (dequeue != NULL) {
                fprintf(file, "%s ", dequeue->data);
                free(dequeue->data);
                free(dequeue);
                dequeue = QUEUE_NodeDequeue(&head);
            }
            i = 0;
        }
        scanf("%s", str);
        i++;
    }
}