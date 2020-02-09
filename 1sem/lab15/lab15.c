#include <stdio.h>
const int n = 1000;
int main() {
    int arr[n*n];
    int min;
    int max;
    int maxi = 0;
    int mini = 0;
    int sum = 0;
    int num = 0;

    while(1) {
        scanf("%d", &num);
        if (num == -1) break;
        for (int i = 0; i < num; ++i) {
            for (int j = 0; j < num; ++j) {
                scanf("%d", &arr[i + j * num]);
                printf("%d ",arr[i + j * num]);
            }
            printf("\n");
        }


        min = arr[0];
        max = arr[0];
        for (int k = 0; k < num; ++k) {
            for (int i = 0; i < num; ++i) {
                sum += arr[i + k * num];
            }
            if (sum >= max) {
                max = sum;
                maxi = k;
            }
            if (sum <= min) {
                min = sum;
                mini = k;
            }
            sum = 0;
        }

        int tmp[num];
        for (int l = 0; l < num; ++l) {
            tmp[l] = arr[l + num * mini];
            arr[l + num * mini] = arr[l + num * maxi];
            arr[l + num * maxi] = tmp[l];
        }
        printf("\n");
        for (int m = 0; m < num; ++m) {
            for (int i = 0; i < num; ++i) {
                printf("%d ", arr[m + num * i]);
            }
            printf("\n");
        }
        printf("\n");
    }
}