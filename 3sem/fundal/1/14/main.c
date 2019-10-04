
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int s, char* args[]) {
    char* inFile = args[1];
    char* tmpFile = "/home/etryfly/Документы/Labs/3sem/fundal/14/tmp";

    FILE* in;
    if (!(in = fopen(inFile, "r"))) {
        printf("File not opened!");
        exit(-1);
    }

    FILE* tmp;
    if (!(tmp = fopen(tmpFile, "w"))) {
        printf("File not opened!");
        exit(-2);
        
    }
    char c;
    while ((c = fgetc(in)) != EOF) {
        if (!isdigit(c)) {
            fprintf(tmp, "%d", c);
        } else {
            fprintf(tmp, "%d", c - '0');
        }
    }

    fclose(tmp);
    fclose(in);

    if (!(in = fopen(inFile, "w"))) {
        printf("Couldn't open file");
        exit(-3);
    }


    if (!(tmp = fopen(tmpFile, "r"))) {
        printf("Couldn't open file");
        exit(-4);
    }

    while (( c = fgetc(tmp)) != EOF) {
        fputc(c, in);
    }

    fclose(tmp);
    fclose(in);
}