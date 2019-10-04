//5. Задана строка символов. Используя указатели,
// переписать строку так, чтобы в начале строки были числа, затем буквы,
// а в самом конце – прочие символы.

#include <stdio.h>
#include <ctype.h>
#include <memory.h>

int main() {
    char str[BUFSIZ], *sPtr = str;
    char out[BUFSIZ], *oPtr = out;
    scanf("%s", str);


    while (*sPtr) {
        if (isdigit(*sPtr)) {
            *oPtr++ = *sPtr;
        }
        sPtr++;
    }

    sPtr = str;

    while (*sPtr) {
        if (isalpha(*sPtr)) {
            *oPtr++ = *sPtr;

        }
        sPtr++;

    }
    sPtr = str;

    while (*sPtr) {
        if (!isdigit(*sPtr)&& !isalpha(*sPtr)) {
            *oPtr++ = *sPtr;

        }
        sPtr++;
    }

    strcpy(str, out);
    printf("%s", str);

}