#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define MAX_INSTRUCTION_LENGTH 20

typedef struct v {
    char* name;
    int data;

} Var;

Var *vars;
int size = 0;

int cmp(Var *a, Var *b) {
    char* aPtr = a->name;
    char* bPtr = b->name;

    for (int i = 0; i < strlen(a->name); ++i) {
        if (*aPtr > *bPtr) return 1;
        if (*aPtr < *bPtr) return -1;
    }
    if (strlen(a->name) < strlen(b->name)) return -1;
    return 0;
}

int cmpChar(char *a, char *b) {
    char* aPtr = a;
    char* bPtr = b;

    for (int i = 0; i < strlen(a); ++i) {
        if (*aPtr > *bPtr) return 1;
        if (*aPtr < *bPtr) return -1;
    }
    if (strlen(a) < strlen(b)) return -1;
    return 0;
}

void setVar(char* name, int data) {
    for (int i = 0; i < size; ++i) {
        if (strcmp(name, vars[i].name) == 0) {
            vars[i].data = data;
            return;
        }
    }
    size++;
    vars = realloc(vars, sizeof(Var) * size);
    vars[size - 1].name = name;
    vars[size - 1].data = data;
    qsort(vars, size, sizeof(Var), (int (*)(const void *, const void *)) cmp);
}

Var getVar(char* name) {
    int l = 0;
    int r = size;
    int c = 0;

    while (l != r) {
        c =  (l + r) / 2;
        if (cmpChar(vars[c].name, name) == 1) {
            r = c;
        } else if (cmpChar(vars[c].name, name) == -1) {
            l = c;
        } else {
            return vars[c];
        }
    }

    return vars[c];
}

void clearBuf(char* buf) {
    char* b = buf;
    while (*b) *b++=0;
}

int main(int argc, char* argv[])
{
    FILE* fIn;
    char c;
    char buf[MAX_INSTRUCTION_LENGTH], *b = buf;

    if (!(fIn = fopen(argv[1], "r")))
    {
        printf("Couldn't open file");
        exit(-1);
    }

    while (!feof(fIn))
    {
        c = fgetc(fIn);
        if (c == ' ' || c == '\n') continue;
        if (c != ';') {
            *b++ = c;
        } else if (c == ';')
        {
            *b++ = c;
            *b = 0;
            b = buf;

            if ((strstr(buf, "print"))) {
                b+= strlen("print");
                if (*b == ';') {
                    for (int i = 0; i < size; ++i) {
                        printf("%s %d\n", vars[i].name, vars[i].data);
                    }
                } else {
                    char nameBuf[250], *ptr = nameBuf;
                    while (*b != ';') {
                        *ptr++ = *b++;
                    }
                    Var var = getVar(nameBuf);
                    printf("%s %d\n", var.name, var.data);

                }
            } else {

                char nameBuf[250], *bufPtr = nameBuf;
                for (int i = 0; *b != '='; ++i) {
                    *bufPtr++ = *b++;
                }
                *bufPtr = 0;
                b++;
                char *name = malloc(sizeof(char) * (strlen(nameBuf) + 1));
                strcpy(name, nameBuf);
                if (isdigit(*b)) {
                    int num = 0;
                    while (*b != ';') {
                        num = num * 10 + (*b - '0');
                        b++;
                    }

                    setVar(name, num);
                } else {
                    char first[250], *aPtr = first;
                    char second[250], *bPtr = second;
                    while (isalpha(*b)) {
                        *aPtr++ = *b++;
                    }
                    char op = *b++;
                    while (isalpha(*b)) {
                        *bPtr++ = *b++;
                    }
                    int l = getVar(first).data;
                    int r = getVar(second).data;

                    switch (op) {
                        case '+':
                            setVar(name, l + r);
                            break;

                        case '*':
                            setVar(name, l * r);
                            break;

                        case '-':
                            setVar(name, l - r);
                            break;

                        case '/':
                            setVar(name, l / r);
                            break;

                        case '%':
                            setVar(name, l % r);
                            break;
                    }


                }

                b = buf;
            }
            b = buf;
            clearBuf(buf);
        }
    }

    for (int j = 0; j < size; ++j) {
        free(vars[j].name);
    }
    free(vars);
    fclose(fIn);
    return 0;
}
