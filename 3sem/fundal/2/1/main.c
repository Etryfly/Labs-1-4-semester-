

#include <stdio.h>
#include <stdlib.h>

int main() {

    char* name = "/home/etryfly/Документы/Labs/3sem/fundal/2/1/data";
    int arr[128];
    int newArr[64];
    int *ptr = newArr;

    FILE* file = NULL;

    if (!(file = fopen(name, "r"))) {
        printf("Couldn't open file");
        exit(-1);
    }

    int c;
    int i = 0;
    int num = 0;
    int count = 0;
    int flag = 1;
    while (!(feof(file))) {

        fscanf(file, "%d", &c);
            //доделать обработку отрицательных и вещ. чисел

        if (i % 2 == 0) {
            *ptr = c;
            ptr ++;
            count ++;
        }
        i++;
    }

    for (int j = 0; j < count; ++j) {
        printf("%d ",newArr[j]);
    }
}