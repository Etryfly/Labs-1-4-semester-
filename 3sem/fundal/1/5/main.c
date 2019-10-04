


#include <stdio.h>

int main() {
    int a,b;
    scanf("%d %d", &a, &b);
    if (a != 0 && b != 0 && a % b == 0 ) printf("%d кратно %d\n", a, b);
    else printf("%d не кратно %d\n", a, b);
}