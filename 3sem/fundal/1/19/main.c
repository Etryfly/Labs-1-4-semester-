
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>


int main() {
    int n;
    scanf("%d", &n);
    int arr1[n];
    int arr2[n];
    int arr3[n];
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {

        arr1[i] = rand() % 10;
        arr2[i] = rand() % 10;
        printf("%d ", arr1[i]);
    }
    printf("\n");
    for (int l = 0; l < n; ++l) {
        printf("%d ", arr2[l]);
    }
    printf("\n");
    int d = arr1[0] - arr2[0];
    int minI = 0;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            if (d > abs(arr1[j] - arr2[i])) {
                d = abs(arr1[j] - arr2[i]);
                minI = i;
            }
        }
        arr3[j] = arr1[j] + arr2[minI];
        minI = 0;
        d = arr1[0];
        printf("%d ", arr3[j]);
    }





}