

#include <stdlib.h>
#include <stdio.h>


int main() {

    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int *result = malloc(sizeof(int) * n);
    int* ptr = result;
    int flag = 1;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] == result[j]) {
                flag = 0;
            }
        }
        if (flag) {
            *ptr++ = arr[i];
            count++;
        }
        flag = 1;
    }

    for (int j = 0; j < count; ++j) {
        printf("%d ",result[j]);
    }
    free(result);
}