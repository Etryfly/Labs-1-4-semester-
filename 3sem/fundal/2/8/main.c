
#include <stdio.h>
#include <bits/nan.h>
#include <stdlib.h>
#include <tgmath.h>
#include <math.h>


double findEps() {
    double eps = 1;
    while (eps > 0) {
        eps/= 2;
    }
    return eps;
}
double powe(double base, int exp) {//проверка на отрицательное
    if (exp == 1) return base;
    if (exp == 0 && fabs(base) < findEps()) return NAN;
    return (exp>0) ? base*powe(base, exp - 1) : powe(base, exp + 1)/base;

}

int main() {
    double base;
    int exp;

    scanf("%lg", &base);
    scanf("%d", &exp);

    printf("%lf\n", powe(base, exp));

}