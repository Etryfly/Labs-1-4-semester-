#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double findEps() {
    double eps = 1;
    while (eps > 0) {
        eps /= 2;
    }
    return eps;
}

double (*func)(double);

double dihotomia(double a, double b, double eps,  double(*func)(double)) {
    while ( b - a > eps) {
        double c = (a + b) / 2;
        if ((*func)(c) * (*func)(b) < 0) {
            a = c;
        } else {
            b = c;
        }
    }

    return (a + b) / 2;
}

double x2(double x) {
    return x + 1;
}

double s(double x) {
    return cos(x);
}

int main() {
    double eps = findEps();
    double k = 10000000;
    printf("%lf\n", dihotomia(-2, 3, 0.000001, x2));
    printf("%lf\n", dihotomia(0, 3, 0.000001, s));
}
