

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


int main() {
    int n;
    scanf("%d", &n);

    int arr[n];

    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 10;
        printf("%d ", arr[i]);
    }

    printf("\n");

    int *max = arr;
    int *min = arr;
    int *ptr = arr;
    for (int j = 0; j < n; ++j) {
        if (*ptr > *max) {
            max = ptr;
        }

        if (*ptr < *min) {
            min = ptr;
        }
        ptr++;
    }

    swap(max, min);

    for (int j = 0; j < n; ++j) {
        printf("%d ", arr[j]);
    }

}