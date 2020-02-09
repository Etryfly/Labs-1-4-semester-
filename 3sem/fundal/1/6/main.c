#include <stdio.h>

int main() {
    int num;
    scanf("%d", &num);
    int arr[7];
    int i = 0;
    for (int j = 0; j < 7; ++j) {
        arr[i] = num % 10;
        num /= 10;
        i++;
    }
    for (int j = 6; j >= 0; --j) {
        printf("%d ",arr[j]);
    }
}