

#include <stdio.h>

int strLen(char* str) {
    char *ptr = str;
    int count = 0;

    while(*ptr) {
        count++;
        ptr++;
    }

    return count;
}

int main() {
    char str[BUFSIZ];
    scanf("%s", str);

    printf("%d\n", strLen(str));
}