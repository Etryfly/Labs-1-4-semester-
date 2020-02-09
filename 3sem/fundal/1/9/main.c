
#include <stdio.h>

int main() {
    int num;
    scanf("%d", &num);
    long sum = 0;
    for (int i = 0; i <= num; ++i) {
        sum += i;
    }
    printf("%u\n", sum);
    

}