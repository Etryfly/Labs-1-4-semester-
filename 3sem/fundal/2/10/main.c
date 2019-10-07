
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int abcCount(char* str) {
    char* ptr = str;
    int count = 0;
    while (*ptr) {
        if (isalpha(*ptr)) {
            count ++;
        }
        ptr++;
    }

    return count;
}


int main(int argc, char** argv) {
    FILE* in;


    if (!(in = fopen(argv[1], "r"))) {
        printf("Couldn't open in");
        exit(-1);
    }

    FILE* out;

    if (!(out = fopen(argv[2], "w"))) {
        printf("Couldn't open out");
        exit(-2);
    }

    char ch;
    char buf[BUFSIZ];
    char *bufptr = buf;
    int i;
    while (!feof(in)) {
         i = 0;


        while ((ch = fgetc(in))!= '\n') {
            if (ch == EOF) break;
            *bufptr++ = ch;
            i++;
        }
        *bufptr = 0;

        fprintf(out, "%d\n", abcCount(buf));

    }

    fclose(out);
    fclose(in);

}