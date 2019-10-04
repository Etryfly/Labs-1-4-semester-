

#include <stdio.h>
#include <stdlib.h>

int main() {

    char* name = "/home/etryfly/Документы/Labs/3sem/fundal/2/2/data";
    int arr[128];
    int *newArr = malloc(sizeof(int) * 128);
    int *ptr = newArr;

    FILE* file = NULL;

    if (!(file = fopen(name, "r"))) {
        printf("Couldn't open file");
        exit(-1);
    }

    int c;

    int num = 0;
    int count = 0;
    int flag = 1;
    while (!(feof(file))) {

        fscanf(file, "%d", &c);
        //доделать обработку отрицательных и вещ. чисел

        if (c % 2 == 0) {
            *ptr = c;
            ptr ++;
            count ++;
        }
    }
    for (int j = 0; j < count; ++j) {
        printf("%d ",newArr[j]);
    }

    free(newArr);

}