

#include <ctype.h>
#include <stdio.h>

int main() {
    char str[BUFSIZ];
    scanf("%s", str);

    char* ptr = str;
    int i = 0;

    while(*ptr) {
        if (i % 2 == 0)
            *ptr = toupper(*ptr);

        i++;
        ++ptr;
    }

    printf("%s", str);
}