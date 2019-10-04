
#include <stdio.h>

//0 1 1 2

int fibo(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    return fibo(n - 1) + fibo(n - 2);
}

int main() {
    int n;
    //scanf("%d",&n);
    for (int i = 1; i <= 15; ++i) {
        printf("%d %d\n",i, fibo(i));
    }


}