


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define OP_COUNT 9

typedef struct var {
    char ch;
    int n;
} var;

var vars[27];
int size = -1;

void addVar(char ch, int n) {

    var v;
    v.ch = ch;
    v.n = n;
    for (int i = 0; i <= size+1; ++i) {
        if (vars[i].ch == ch) {
            return;
        }
    }
    vars[++size] = v;
}

int getVar(char ch) {
    for (int i = 0; i <= size+1; ++i) {
        if (vars[i].ch == ch) {
            return vars[i].n;
        }
    }
}


int varsPlus1() {
    int i = 0;
    int state = 0;
    for (i = size; i >= 0; --i) {
        if (vars[i].n == 0 && state == 0) {
            vars[i].n = 1;
            return i;
        } else if (vars[i].n == 1 && state == 0) {
            state = 1;
            vars[i].n = 0;
        } else if (vars[i].n == 0 && state == 1) {
            vars[i].n = 1;
            return i;
        } else if (vars[i].n == 1 && state == 1) {
            vars[i].n = 0;
        }
    }
    return i;
}

typedef struct TreeNode {
    char* ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* data;
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
    if (*stack == NULL) return NULL;
    return *stack;
}

StackNode* STACK_pop(StackNode** stack) {
    if (*stack == NULL) return NULL;
    StackNode* result = *stack;
    *stack = (*stack)->next;
    return result;
}

TreeNode* TREE_createNode(char* c) {
    TreeNode* result = malloc(sizeof(TreeNode));
    result->ch = malloc(sizeof(char) * (strlen(c) + 1));
    strcpy(result->ch, c);
    result->left = NULL;
    result->right = NULL;
    return result;
}

StackNode* STACK_createNode(TreeNode* node) {
    StackNode* result = malloc(sizeof(StackNode));
    result->data = node;
    result->next = NULL;
    return result;
}

char * op[OP_COUNT] = {
        "&", "|", "~", "->", "+>", "<>", "=", "!", "?"
};

int isOp(char* buf) {
    char **cm;
    for (cm = op; cm - op < OP_COUNT; cm++)
    {
        if (strstr(buf, *cm) == buf)
        {
            return cm - op;
        }
    }

    return -1;
}

int isOpGreater(char* a, char* b) {
//    3(~), 2(?,!,+>,&), 1(|, ->, <>, =)
    int l = 0;
    int r = 0;
    if (strstr(a, "~") == a) l = 3;
    if (strstr(a, "?") == a || strstr(a, "!") == a || strstr(a, "+>") == a || strstr(a, "&") == a) l = 2;
    if (strstr(a, "|") == a || strstr(a, "->") == a || strstr(a, "<>") == a || strstr(a, "=") == a) l = 1;

    if (strstr(b, "~") == b) r = 3;
    if (strstr(b, "?") == b || strstr(b, "!") == b || strstr(b, "+>") == b || strstr(b, "&") == b) r = 2;
    if (strstr(b, "|") == b || strstr(b, "->") == b || strstr(b, "<>") == b || strstr(b, "=") == b) r = 1;
    return l - r;
}


StackNode* charToStackNode(char c) {
    char str[2];
    str[0] = c;
    str[1] = 0;
    TreeNode* node = TREE_createNode(str);
    StackNode* stackNode = STACK_createNode(node);
    return stackNode;
}


StackNode* strToStackNode(char* c) {
    TreeNode* node = TREE_createNode(c);
    StackNode* stackNode = STACK_createNode(node);
    return stackNode;
}

int not(int r) {
    if (r == 0) return 1;
    return 0;
}

int eval(TreeNode* root) { // "&", "|", "~", "->", "+>", "<>", "=", "!", "?"
    int opNumber = isOp(root->ch);
    if (opNumber != -1) {
        int l = 0;
        int r = 0;
        if (root->right) {
            r = eval(root->right);
        }
        if (root->left) {
            l = eval(root->left);
        }
        switch (opNumber) {
            case 0:
                return l&r;

            case 1:
                return l | r;

            case 2:
                return not(r);

            case 3:
                return not(l) | r;

            case 4:
                return not(not(l) | r);

            case 5:
                return (not(l) & r) | (l & not(r));

            case 6:
                return (l & r) | (not(l) & not(r));

            case 7:
                return not(l) | not(r);

            case 8:
                return not(l) & not(r);
        }
    } else {
        if (isdigit(root->ch[0])) {
            return root->ch[0] - '0';
        }
        return getVar(root->ch[0]);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    FILE* file;
    if (argc < 2 || !(file = fopen(argv[1], "r"))) {
        exit(-1);
    }
    char c;
    char buf[BUFSIZ], *ptr = buf;
    while (1) {
        fscanf(file, "%c", &c);
        if (feof(file)) break;
        if (c != ' ') {
            *ptr++ = c;
        }
    }
    fclose(file);

    ptr = buf;

    StackNode* opStack = NULL;
    StackNode* treeStack = NULL;


    while (*ptr != 0) {
        int opNum = -1;
        if (isalpha(*ptr) || isdigit(*ptr)) {
            if (isalpha(*ptr)) {
                addVar(*ptr, 0);
            }
            StackNode *stackNode = charToStackNode(*ptr);
            STACK_push(&treeStack, stackNode);
            ptr++;
        } else if (((opNum = isOp(ptr)) != -1) && (*ptr != ')') &&
                   (*ptr == '(' || (STACK_top(&opStack) != NULL && ((((opNum = isOp(ptr)) != -1) && isOpGreater(op[opNum], STACK_top(&opStack)->data->ch) > 0 )||
                     STACK_top(&opStack)->data->ch[0] == ')')))) {
            StackNode *node = strToStackNode(op[opNum]);
            STACK_push(&opStack, node);
            ptr+= strlen(op[opNum]);
        } else {
            while (STACK_top(&opStack) != NULL && ((*ptr == ')' && STACK_top(&opStack)->data->ch[0] != '(')
                                                   || ((opNum != -1) && isOpGreater(op[opNum], STACK_top(&opStack)->data->ch) > 0))) {
                TreeNode *treeNode = STACK_pop(&opStack)->data;
                treeNode->right = STACK_pop(&treeStack)->data;
                if (STACK_top(&treeStack)) {
                    treeNode->left = STACK_pop(&treeStack)->data;
                }
                STACK_push(&treeStack, STACK_createNode(treeNode));
            }

            if (STACK_top(&opStack) && STACK_top(&opStack)->data->ch[0] == '(' && *ptr == ')')
                STACK_pop(&opStack);
            if (*ptr != ')') {
                STACK_push(&opStack, strToStackNode(op[opNum]));
                ptr += strlen(op[opNum]);
            } else {
                ptr++;
            }
        }
    }

        while (STACK_top(&opStack) != NULL) {
            StackNode* node = strToStackNode(STACK_pop(&opStack)->data->ch);
            node->data->right = STACK_pop(&treeStack)->data;
            if (STACK_top(&treeStack)) {
                node->data->left = STACK_pop(&treeStack)->data;
            }
            STACK_push(&treeStack, node);
        }

        for (int j = 0; j <= size; ++j) {
            printf("%c ", vars[j].ch);
        }

        printf("F\n");

        for (int i = 0; i < (1 << (size + 1)); i ++) {
            for (int j = 0; j <= size; ++j) {
                printf("%d ", vars[j].n);
            }

            printf("%d\n", eval(STACK_top(&treeStack)->data));
            varsPlus1();
//            printf("\n");
        }
 }
