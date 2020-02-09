
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* first;
    if (!( first = fopen("/home/etryfly/Документы/Labs/3sem/fundal/15/1", "r"))) {
        printf("Couldn't open file1");
        exit(-1);
    }  

    FILE* second;
    if (!( second = fopen("/home/etryfly/Документы/Labs/3sem/fundal/15/2", "r"))) {
        printf("Couldn't open file2");
        exit(-2);
    }  

    FILE* third;
    if (!( third = fopen("/home/etryfly/Документы/Labs/3sem/fundal/15/3", "w"))) {
        printf("Couldn't open file3");
        exit(-2);
    }  
    int i = 0;
    int isEndReached = 0;
    char c;
    while (!isEndReached) {
        while ( 1)
        {
            c = fgetc(first);
            if (c == EOF) {
                isEndReached = 1;
                fputc(' ', third);
                break;
            }
            if (c == ' ') {
                fputc(' ', third);
                break;
            } 
            fputc(c, third);
        }
        
        while ( 1)
        {
            c = fgetc(second);
            if (c == EOF) {
                isEndReached = 1;
                fputc(' ', third);
                break;
            }
            if (c == ' ') {
                fputc(' ', third);
                break;
            } 
            fputc(c, third);
        }
        
    }

    fclose(first);
    fclose(second);
    fclose(third);

}