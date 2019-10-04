

#include <stdio.h>

int main() {
    char* name = "/home/etryfly/Документы/Labs/3sem/fundal/3/fileFor3";
    char* nametmp3 = "/home/etryfly/Документы/Labs/3sem/fundal/3/tmp3";

    FILE *file;

    //file -> ... -> tmp

    if (!(file = fopen(name, "r"))) {
        printf("File not opened");
        return 0;
    }

    FILE *tmp;

    if (!(tmp = fopen(nametmp3, "w"))) {
        printf("File not opened");
        return 0;
    }
    char c;
    while (!feof(file)) {
        c = getc(file);
        if (!( c > '0' && c < '9')) {
            putc(c, tmp);
        }
    }

    fclose(file);
    fclose(tmp);


    //tmp -> file

    if (!(file = fopen(name, "w"))) {
        printf("File not opened");
        return 0;
    }


    if (!(tmp = fopen(nametmp3, "r"))) {
        printf("File not opened");
        return 0;
    }

    while ((c = fgetc(tmp)) != EOF) {
        putc(c, file);
    }

    fclose(file);
    fclose(tmp);



}