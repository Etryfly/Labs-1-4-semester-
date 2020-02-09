// На вход программе, через аргументы командной строки, подается файл.
// Необходимо прочитать файл и в файл трассировки (выходной файл) написать сколько раз в каждой строче встречаются буквы.
#include <stdio.h>
#include <stdlib.h>

int main(int s, char** args) {
    char arr[52];
    for (int i = 0; i < 26; ++i) {
        arr[i] = 'a' + i;
    }

    for (int i = 26; i < 52; ++i) {
        arr[i] = 'A' + i - 26;
    }
    int count[52] = {0};

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
            for (int i = 0; i < 52; ++i) {
                if (arr[i] == c) {
                    count[i] ++;
                }
            }
        } else {
            for (int i = 0; i < 52; ++i) {
                if (count[i] != 0)
                fprintf(out, "%c%d ", arr[i], count[i]);
                count[i] = 0;
            }
            fprintf(out, "\n-----------------------------------------------------------\n\n\n");

        }
    }

    fclose(out);
    fclose(in);


}