


#include <stdio.h>

int main() {
    int n;
    int count = 0;
    scanf("%d", &n);
    if (n!=0) {
        for (int i = 1; i <= 100; ++i) {
            if (i % n == 0) {
                printf("%d\n", i);
                count++;
            }
        }
    }

    if (!count) {
        printf("Кратных чисел нет\n");
    }
}