#include <stdarg.h>
#include <stdio.h>
#include <math.h>


double mn(double x, int n, ...) {
    va_list args;
    va_start(args, n);

    double result = 0;

    for (int i = 0; i <= n; ++i) {
        double k = va_arg(args, double);
        result += k*pow(x, n - i);
    }


    return result;
}


int main() {
    printf("%lf\n", mn(2, 2, 1.,1.,1.));
    printf("%lf\n", mn(2, 2, 0., 1., 1.));
    printf("%lf\n", mn(2, 2, 0., 1., 0.));
    printf("%lf\n", mn(2, 2, 0., 0., 1.));
    printf("%lf\n", mn(2, 3, 0., 0., 1., 1.));
    printf("%lf\n", mn(2, 3, 1., 0., 1., 1.));

}