
#include <stdio.h>

unsigned long int pow(int base, int exp) {
    unsigned long int result = (unsigned long) base;
    for (int i = 1; i <= exp; ++i) {
        result *=  base;
    }
    return result;
}

int main() {
    int num;
    scanf("%d", &num);
    for (int i = 1; i <= 10 ; ++i) {
        for (int j = 0; j < num; ++j) {
            printf("%11lu ", pow(i, j));
        }
        printf("\n");
    }
}
