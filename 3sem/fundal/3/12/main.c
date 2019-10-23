

#include <zconf.h>
#include <stdio.h>
#include <ctype.h>
#include <memory.h>

#define STACK_SIZE 250

char stack[STACK_SIZE];
int ptr = -1;

void pushToStack(char c) {
    ptr++;
    stack[ptr] = c;
}

char popFromStack() {
    if (ptr == -1) return NULL;
    char r = stack[ptr];
    ptr--;
    return r;
}

char topFromStack() {
    if (ptr == -1) return NULL;
    return stack[ptr];
}

int main(int argc, char* argv[]) {
    FILE* file;
    for (int i = 1; i < argc; ++i) {

        if (!(fopen(argv[i], "r"))) {
            printf("Couldn't open %s\n", argv[i]);
            continue;
        }
        char buf[STACK_SIZE * 2];
        int size = ptr;
        char result[STACK_SIZE], *resptr = result;

        while (!feof(file)) {
            fscanf(file, "%s", buf);
            for (int k = 0; k < strlen(buf); ++k) {
                if (isdigit(buf[k])) {
                    *resptr++ = buf[k];
                } else {
                    if (buf[k] == '(') {
                        pushToStack('(');
                    }


                }
            }
        }
    }
}


