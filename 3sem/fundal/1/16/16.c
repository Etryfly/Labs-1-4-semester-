

#include <stdio.h>
#define BUFSIZE 100
int main() {
    char* name = "/home/etryfly/Документы/Labs/3sem/16/file";


    FILE *file;

    if (!(file = fopen(name, "r"))) {
        printf("File not opened");
        return 0;
    }

    char buf[BUFSIZE];
    char c;
    while (!feof(file)) {
        c = getc(file);
        if ()
    }



}