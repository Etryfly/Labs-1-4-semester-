

#include <stdio.h>
#include <math.h>

int isSimple(int num) {
    for (int i = 2; i < num; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n != 0) {
        if (isSimple(abs(n))) printf("%d простое \n", n);
        else printf("%d составное \n", n);
        scanf("%d", &n);
    }
}
