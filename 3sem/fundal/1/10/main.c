
#include <stdio.h>

int main() {
    int num;
    scanf("%d", &num);
    long p = 1;
    for (int i = 1; i <= num; ++i) {
        p *= i;
    }
    printf("%lu\n", p);
    

}