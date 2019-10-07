
#include <stdlib.h>
#include <stdio.h>


int countOf1InBinary(int num) {
    int count = 0;
    while (num != 0) {
        if (num % 2 != 0) count ++;
        num /= 2;
    }
    return count;
}

int maxCountOfSeries1InBinary(int num) {
    int maxCount = 0;
    int count = 0;

    while (num != 0) {
        if (num % 2 != 0) count ++;
        else {
            if (count > maxCount) maxCount = count;
            count = 0;
        }
        num /= 2;
    }
    if (count > maxCount) maxCount = count;
    return maxCount;
}

int* first(int k, int l) {
    int max = 1 << k;
    int* result = malloc(sizeof(int) * BUFSIZ), *ptr = result;
    for (int i = 1 << (k-1); i < max; ++i) {
        if (countOf1InBinary(i) == l) {
            *ptr++ = i;
        }
    }
    *ptr = 0;
    return result;
}

int* second(int k, int l) {
    int max = 1 << k;
    int* result = malloc(sizeof(int) * BUFSIZ), *ptr = result;
    for (int i = 1 << (k-1); i < max; ++i) {
        if (maxCountOfSeries1InBinary(i) == l && countOf1InBinary(i) == l) {
            *ptr++ = i;
        }
    }
    *ptr = 0;
    return result;
}


int main() {
    int k, l;
    scanf("%d", &k);
    scanf("%d", &l);

    printf("FIRST:\n");
    int *result1 = first(k, l);

    while (*result1 != 0)
        printf("%d\n", *result1++);

    printf("\n");
    printf("\n");
    printf("SECOND:\n");
    int *result2 = second(k, l);

    while (*result2 != 0)
        printf("%d\n", *result2++);

    free(result1);
    free(result2);

}

