
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_STACK_SIZE 10

typedef struct _stack {
    char *data;
    int size;
    int indexOfTop;
} Stack;

Stack* StackCreate() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->indexOfTop = -1; // -1 пустой стек, 0 1 элемент в стеке
    stack->size = DEFAULT_STACK_SIZE;
    stack->data = malloc(sizeof(char) * DEFAULT_STACK_SIZE);
    return stack;
}

void StackPush(Stack* stack, char data) {
    if (stack->indexOfTop+1>stack->size) {
        stack->size*=2;
        stack->data = realloc(stack->data, stack->size*sizeof(char));
    }
    stack->data[stack->indexOfTop + 1] = data;
    stack->indexOfTop++;
}

char StackPop(Stack* stack) {
    if (stack->indexOfTop >= 0) {
        char c = stack->data[stack->indexOfTop];
        stack->indexOfTop--;
        return c;
    }
    return 0;
}

int main() {
    char* name = "/home/etryfly/Документы/Labs/3sem/OS/1/1txt";
    FILE* file;
    if (!(file = fopen(name, "r"))) {
        printf("Couldn't open file");
        exit(-1);
    }
    int isValid = 1;
    char c;
    Stack* stack = StackCreate();
    while ((c = fgetc(file)) != EOF) {
        //2 ситуации: пришла открывающая или закрывающая скобка

        if (c == '{' || c == '(' || c == '[' || c == '<') {
            StackPush(stack, c);
        } else {
            switch (c) {
                case '}':
                    if (StackPop(stack) == '{') continue;
                    else {
                       isValid = 0;
                        break;
                    }

                case ']':
                    if (StackPop(stack) == '[') continue;
                    else {
                        isValid = 0;
                        break;
                    }

                case '>':
                    if (StackPop(stack) == '<') continue;
                    else {
                        isValid = 0;
                        break;
                    }

                case ')':
                    if (StackPop(stack) == '(') continue;
                    else {
                        isValid = 0;
                        break;
                    }


            }

        }



    }

    char* out = "/home/etryfly/Документы/Labs/3sem/OS/1/1.txt";
    FILE* outStream;
    if (!(outStream = fopen(out, "w" ))) {
        printf("Couldn't open out file");
        exit(-2);
    }



    if (stack->indexOfTop != -1 || !isValid) {
        printf("Brackets are not valid");
        fprintf(outStream, "Brackets are not valid");

    } else {
        printf("Brackets are valid");
        fprintf(outStream, "Brackets are valid");
    }
}


