

#include <stdio.h>
#include <stdarg.h>
#include <math.h>

double geom(int count,...) {
    va_list args;
    va_start(args, count);
    double p = 1;
    for (int i = 0; i < count; ++i) {
        p *= va_arg(args, double);
    }
    va_end(args);
    return pow(p, 1.0/count);
}

int main() {
    printf("Geom:%g\n", geom(2, 2., 5.));
}