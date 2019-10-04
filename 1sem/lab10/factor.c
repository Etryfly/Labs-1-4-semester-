#include <stdio.h>


int factor(int n) {
    return n == 1 ? 1 : factor(n - 1)*n;
}

int main() {
    int n;
    for (int i = 1; i <= 15; ++i) {
        printf("%d %d\n",i, factor(i));
    }

}

