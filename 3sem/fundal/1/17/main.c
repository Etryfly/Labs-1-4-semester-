
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000

int char2int(char c) {
    return c - '0';
}

int main() {
    FILE* file;
    if (!( file = fopen("/home/etryfly/Документы/Labs/3sem/fundal/17/data", "r"))) {
        printf("Couldn't open file1");
        exit(-1);
    }

    int *buf = malloc(sizeof(int)* BUFFER_SIZE);
    char c;
    int *ptr = buf;
    int minBase = 0;
    int intInBase = 0;
    int intInTen = 0;

    *ptr = -1;
    int flag = 1;
    char prev;
    while (flag) {
        flag = ((c = fgetc(file) )!= EOF);
        if (c != ' ' && c != EOF) {
            int digit = char2int(c);
            if (digit >= minBase) minBase = digit + 1;
            *++ptr = digit;
        } else if (prev != ' '){
            ptr++;
            *ptr = -1;

            while (*--ptr != -1) {

            }

            while (*++ptr != -1 ) {
                intInTen = intInTen * minBase + *ptr;
                intInBase = intInBase * 10 + *ptr;
            }

            printf("Int in base: %d, base: %d, int in ten: %d \n", intInBase, minBase, intInTen);
            minBase = 0;
            intInBase = 0;
            intInTen = 0;

        }
        prev = c;

    }

    fclose(file);

}