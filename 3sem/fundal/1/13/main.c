
#include <stdio.h>
#include <stdlib.h>

int main() {
    char* inFile = "/home/etryfly/Документы/Labs/3sem/fundal/13/IN";
    char* outFile = "/home/etryfly/Документы/Labs/3sem/fundal/13/out";
    char* tmpFile = "/home/etryfly/Документы/Labs/3sem/fundal/13/tmp";

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
    char *buf[3];
    for (int i = 0; i < 3; ++i) {
        buf[i] = malloc(sizeof(char) * 100);
    }

    int count = 0;
    int i = 0;
    while ((c = fgetc(in)) != EOF) {
        if (c != '\n') {
            if (c != ' ') {
                buf[count][i] = c;
                i++;

            } else {
                i = 0;
                count ++;
            }
        } else {
            fprintf(tmp, "%s %s %s\n", buf[2], buf[0], buf[1]);
            count = 0;
            i = 0;

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