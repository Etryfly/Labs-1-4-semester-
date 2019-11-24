


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OP_COUNT 9

typedef struct TreeNode {
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    char ch;
    struct StackNode* next;
} StackNode;

void STACK_push(StackNode** stack, StackNode* node) {
    if (*stack == NULL) {
        *stack = node;
    } else {
        node->next = *stack;
        *stack = node;
    }
}

StackNode* STACK_top(StackNode** stack) {
    return *stack;
}

StackNode* STACK_pop(StackNode** stack) {
    StackNode* result = *stack;
    *stack = (*stack)->next;
    return result;
}

TreeNode* TREE_createNode(char c) {
    TreeNode* result = malloc(sizeof(TreeNode));
    result->ch = c;
    return result;
}

char * op[OP_COUNT] = {
        "&", "|", "~", "->", "+>", "<>", "=", "!", "?"
};

int main(int argc, char* argv[]) {
    FILE* file;
    if (argc < 2 || !(file = fopen(argv[1], "r"))) {
        exit(-1);
    }
    char c;
    char buf[BUFSIZ], *ptr = buf;
    while (!(feof(file))) {
        fscanf(file, "%c", &c);
        if (c != ' ') {
            *ptr++ = c;
        }
    }
    char **cm;
    for (cm = op; cm - op < OP_COUNT; cm++)
    {
        if (strstr(buf, *cm) == buf)
        {
            break;
        }
    }
    int commandId = cm - op;
}