
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

int main() {
    int n;
    scanf("%d", &n);
    srand(time(NULL));
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    int max = arr[0];
    int min = arr[0];
    int iMax = 0;
    int iMin = 0;

    for (int j = 0; j < n; ++j) {
        if (arr[j] > max) {
            max = arr[j];
            iMax = j;
        }
        if (arr[j] < min) {
            min = arr[j];
            iMin = j;
        }
    }

    printf("Max: %d Min: %d \n", max, min);

    arr[iMax] = min;
    arr[iMin] = max;
    for (int k = 0; k < n; ++k) {
        printf("%d ", arr[k]);
    }

}