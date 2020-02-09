


#include <stdio.h>
#include <stdlib.h>

double EPS;

double getEps() {
    double eps = 1;
    while (eps != 0) {
        eps /= 2;
    }
    return eps;
}

int isDoubleEqual(double a, double b) {
    if (((a-b) <= EPS) && ((b-a) <= EPS)) return 1;

    return 0;
}

int main() {
    int a,b,c;
    scanf("%d %d %d", &a, &b, &c);
    EPS = getEps();
    if (isDoubleEqual(a*a + b*b, c*c)) {
        printf("a, b, c - стороны прямоугольного треугольника\n");
    } else {
        printf("a, b, c - не могут быть сторонами прямоугольного треугольника\n");
    }
}