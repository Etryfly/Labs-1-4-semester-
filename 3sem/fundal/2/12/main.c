

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>

int substr(char* str, char* substr) {
    char* ptrStr = str;
    char* ptrSubstr = substr;
    int startOfSubstrInStr = 0;
    int i = 0;
    while (*ptrSubstr && *ptrStr) {

        if (*ptrStr == *ptrSubstr) {
            ptrSubstr++;
        } else {
            ptrSubstr = substr;
            startOfSubstrInStr = i+1;
        }

        ptrStr++;

         i++;
    }

    if (*ptrSubstr) return -1;
    else return startOfSubstrInStr;

}

void pushBackNextInBuffer(char* buf, char c) {
    strcpy(buf, buf+1);
    buf[strlen(buf) - 1] = c;
}

void searchSubstr(char* sub, int n, ...) {
    va_list args;
    va_start(args, n);

    for (int i = 0; i < n; ++i) {
        char* name = va_arg(args, char*);
        FILE* file;

        if (!(file = fopen(name, "r"))) {
            printf("Couldn't open file");
            continue;
        }
        char buf[strlen(sub)], *ptr = buf;
        while (!feof(file) && strlen(buf) <= strlen(sub)) {
            *ptr++ = fgetc(file);
        }
        int index = 0;
        while (!feof(file)) {
            buf[strlen(sub)] = 0;
            if (strcmp(sub,buf) != 0) {
                pushBackNextInBuffer(buf, fgetc(file));
                index++;
            } else {
                printf("Substr in str start:%d File: %s", index, name);
                fclose(file);
            }
        }

        fclose(file);

    }

    printf("Substr in str was not found");
}

int main() {
    char* name1 = "a";
    char* name2 = "b";
    char* name3 = "c";
    searchSubstr("qw\nv", 3, name1, name2, name3);
}