

#include <zconf.h>
#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdlib.h>

#define STACK_SIZE 250


#define IS_OPERATOR(c) (c == '-' || c == '+' || c == '/' || c == '*')

typedef struct String {
    char data[BUFSIZ];
} String;

String stack[STACK_SIZE];
int ptr = -1;

void pushToStack(String c) {
    ptr++;
    stack[ptr] = c;
}


String popFromStack() {
//    if (ptr == -1) return ;
    return stack[ptr--];
}

String topFromStack() {
    return stack[ptr];
}

int isOpGreater(String left, char b) {
    int l = 0;
    int r = 0;
    char a = left.data[0];
    if (a == '/' || a == '*') l = 2;
    if (a == '-' || a == '+') l = 1;
    if (b == '/' || b == '*') r = 2;
    if (b == '-' || b == '+') r = 1;
    return l - r;
}

void error(char* bufptr, char* name, int j, char* buf) {
    ptr = -1;
    char filename[BUFSIZ];
    sprintf(filename, "%s-err", name);
    FILE *err = fopen(filename, "a");
    if (err == NULL) {
        printf("FAIL");
        exit(-5);
    }
    bufptr = buf;
    for (int k = 0; k < j; ++k) {
        while (*bufptr != '\n' && *bufptr != EOF) {
            bufptr++;
        }
        bufptr++;
    }

    fprintf(err, "%d -> ", j);
    while (*bufptr != '\n' && *bufptr != EOF && *bufptr) {
        fprintf(err, "%c", *bufptr);
        bufptr++;
    }
    fprintf(err, "\n");
    bufptr++;
    printf("Err\n");
    fclose(err);
}

int main(int argc, char *argv[]) {
    FILE *file;
    int j;
    for (int i = 1; i < argc; ++i) {
        if (!(file = fopen(argv[i], "r"))) {
            printf("Couldn't open %s\n", argv[i]);
            continue;
        }
        printf("\n\n\n\n%s\n", argv[i]);
        char c;
        char result[STACK_SIZE], *resptr = result;
        char buf[BUFSIZ] = {0}, *bufptr = buf;
        while (!feof(file)) {
            fscanf(file, "%c", &c);
            if (feof(file)) break;
            if (c == ' ') continue;
            *bufptr++ = c;
        }
        fclose(file);

        *bufptr = 0;
        bufptr = buf;
        j = 0;
        while (*bufptr) {

            int flag = 0;
            resptr = result;
            char *t = bufptr;
            while (*t != '\n' && *t != 0) {
                printf("%c", *t++);
            }
            printf(" ");
            while (*bufptr && *bufptr != '\n') {
                flag = 0;
                if (isdigit(*bufptr)) {

                    while (isdigit(*bufptr)) {
                        *resptr++ = *bufptr++;
                    }
                    *resptr++ = ' ';
                } else if (*bufptr == '(') {
                    String p;
                    p.data[0] = *bufptr++;
                    pushToStack(p);
                } else if (*bufptr == ')') {
                    if (ptr == -1) {
                        error(bufptr, argv[i], j, buf);
                        j++;
                        while (*bufptr != '\n' && *bufptr != 0) bufptr++;
                        bufptr++;
                        flag = 1;
                        continue;

                    }
                    if (topFromStack().data[0] != '(') {
                        while (ptr != -1 && topFromStack().data[0] != '(') {
                            char *n;
                            if (isdigit(topFromStack().data[0])) {
                                String str = popFromStack();
                                n = str.data;
                                while (n) {
                                    *resptr++ = *n++;
                                }
                            } else {
                                *resptr++ = popFromStack().data[0];
                            }

                            *resptr++ = ' ';

                            bufptr++;
                        }
                    } else {
                        bufptr++;
                    }
                    if (ptr == -1) {
                        error(bufptr, argv[i], j, buf);
                        j++;
                        while (*bufptr != '\n' && *bufptr != 0) bufptr++;
                        bufptr++;
                        flag = 1;
                        continue;
                    }
                    popFromStack();
                } else if (IS_OPERATOR(*bufptr)) {
                    if (ptr != -1) {
                        String top = topFromStack();

                        if (isOpGreater(top, *bufptr) == 0 || isOpGreater(top, *bufptr) == 1) {
                            *resptr++ = popFromStack().data[0];
                            *resptr++ = ' ';
                        }
                    }
                    String str;
                    str.data[0] = *bufptr;
                    pushToStack(str);
                    bufptr++;
                } else {
                    //error
                }
            }
            if (flag) {

                continue;
            }
            while (ptr != -1 && topFromStack().data[0] != 0) {
                if (topFromStack().data[0] == '(' || topFromStack().data[0] == ')') {
                    error(bufptr, argv[i], j, buf);
                    j++;
                    while (*bufptr != '\n' && *bufptr != 0) bufptr++;
                    flag = 1;
                    break;
                }
                char *n;
                if (isdigit(topFromStack().data[0])) {
                    String str = popFromStack();
                    n = str.data;
                    while (n) {
                        *resptr++ = *n++;
                    }
                } else {
                    *resptr++ = popFromStack().data[0];
                }

                *resptr++ = ' ';
            }
            if (flag) {
                if (*bufptr == '\n') bufptr++;
                continue;

            }
            *resptr = 0;



            resptr = result;


            while (*resptr) {
                if (isdigit(*resptr)) {
                    String str;
                    sscanf(resptr, "%s", str.data);
                    resptr += strlen(str.data) + 1;
                    pushToStack(str);
                } else if (IS_OPERATOR(*resptr)) {
                    String right = popFromStack();
                    String left = popFromStack();
                    int l;
                    int r;
                    sscanf(left.data, "%d", &l);
                    sscanf(right.data, "%d", &r);
                    String str;
                    switch (*resptr) {
                        case '+':
                            sprintf(str.data, "%d", l + r);
                            break;

                        case '-':
                            sprintf(str.data, "%d", l - r);
                            break;

                        case '*':
                            sprintf(str.data, "%d", l * r);
                            break;

                        case '/':
                            sprintf(str.data, "%d", l / r);
                            break;
                    }

                    pushToStack(str);

                    resptr += 2;
                } else {
                    printf("error");
                }
            }



            printf("%s\n", popFromStack().data);
            bufptr++;
            j++;
            ptr = -1;
        }
    }
}


