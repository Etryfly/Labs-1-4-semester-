

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

void reverse(char* str) {
    char* buf = malloc(sizeof(char) * strlen(str));
    char* strptr = str;
    char* bufptr = buf;

    while (*strptr) {
        strptr++;
    }

    while (*--strptr) {
        *bufptr++ = *strptr;
    }

    bufptr = buf;
    strptr++;
    while (*bufptr) {
        *strptr++ = *bufptr++;
    }
    free(buf);
}


int main() {
    char str[BUFSIZ];

    scanf("%s", str);
    reverse(str);
    printf("%s\n", str);

}