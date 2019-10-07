

#include <stdio.h>
#include <stdlib.h>

char NUM_AND_ALPHABET[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int countOfGroupR(int num, int r) {
    int count = 0;
    while (num != 0) {
        num = num >> r;
        count++;
    }
    return count;
}



//110110(2) -> 54(10) -> 312(4)
char* cc(int num, int r) {
    int tmp[BUFSIZ], *ptr = tmp;
    char *result = malloc(sizeof(char) * BUFSIZ), *rPtr = result;
    int mask = 0;
    int len = countOfGroupR(num,r);

    for (int i = 0; i < r; ++i) {
        mask <<= 1;
        mask |= 1;
    }
    *ptr++ = -1; // для того, чтобы найти начало числа при выводе
    for (int j = 0; j < len; ++j) {
        *ptr++ = num & mask;
        num >>= r;

    }

    while (*--ptr != -1) {
        *rPtr++ = NUM_AND_ALPHABET[*ptr];
    }
    return result;
}

int main() {
    int num, r;

    scanf("%d", &num);
    scanf("%d", &r);
    printf("%s", cc(num,r));
}