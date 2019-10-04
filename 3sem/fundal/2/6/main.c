

#include <memory.h>
#include <stdio.h>

void strc(char* dest, char* source) {
    char* ptr = dest + strlen(dest);
    char* sourcePtr = source;
    while (*sourcePtr) {
        *ptr++ = *sourcePtr;
        sourcePtr++;
    }

}

int main() {
    char dest[BUFSIZ];
    char source[BUFSIZ];

    scanf("%s", dest);
    scanf("%s", source);

    strc(dest, source);

    printf("%s", dest);
}