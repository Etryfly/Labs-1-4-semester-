// На вход программе, через аргументы командной строки, подается файл.
// Необходимо прочитать файл и в файл трассировки (выходной файл) написать сколько раз в каждой строче встречаются буквы.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int s, char** args) {
    int count = 0;

    char* inputFileName;
    //inputFileName = "/home/etryfly/Документы/Labs/3sem/fundal/11/data";
    inputFileName = args[1];
    char* outputFileName;
    //outputFileName = "./out";
    outputFileName = args[2];

    FILE* in;
    if (!(in = fopen(inputFileName, "r"))) {
        printf("File not opened!");
        exit(1);
    }

    FILE* out;
    if (!(out = fopen(outputFileName, "w"))) {
        printf("File not opened!");
        exit(2);
    }
    char c;
    while((c = fgetc(in)) != EOF) {
        if (c != '\n') {
            if (!isdigit(c) && !isalpha(c) && c != ' ') {
                count++;
            }
        } else {

            fprintf(out, "%d \n", count);
            count = 0;
        }
    }

    fclose(out);
    fclose(in);


}