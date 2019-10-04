

#include <stdio.h>

void printArr(int* arr,int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void shellSort(int n, int* arr) {
    int j;
    for (int step = n/2; step > 0; step/=2) {

        for (int i = step; i < n; i++) {
            int tmp = arr[i];
            for ( j = i; j>=step; j-=step) {
                if (tmp < arr[j - step]) {
                    arr[j] = arr[j - step];
                } else break;
            }
            arr[j] = tmp;
        }
    }
}



int main() {
    int n;
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        int data;
        scanf("%d", &data);
        arr[i] = data;
    }

    shellSort(n, arr);

    printArr(arr, n);
}