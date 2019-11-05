

#include <stdlib.h>

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

void LIST_NodePush(Node* node, Node** listFirstElement) {
    if (*listFirstElement == NULL) {
        *listFirstElement = node;
        return;
    }

    Node* cur = *listFirstElement;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
}

Node* STACK_NodePop(Node** top) {
    Node* result = *top;
    *top = (*top)->next;
    return result;
}

Node* QUEUE_NodeDequeue(Node** head) {
    Node* result = *head;
    *head = (*head)->next;
    return result;
}

int main() {
    char str[250];
    
}