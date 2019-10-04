
#include <stdio.h>

double pow(double base, int exp) {//проверка на отрицательное
    if (exp == 1) return base;

    return (exp>0) ? base*pow(base, exp - 1) : pow(base, exp + 1)/base;

}

int main() {
    double base;
    int exp;

    scanf("%lg", &base);
    scanf("%d", &exp);

    printf("%lf\n", pow(base, exp));

}