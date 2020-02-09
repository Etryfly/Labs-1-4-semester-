


#include <stdio.h>
#include <math.h>


int main() {

    float a,b,c;
    double d;
    scanf("%f %f %f", &a, &b, &c);
    d = b*b - 4 * a * c;
    if (d < 0) printf("D = %lf, корни комплексные\n",d);
    else {
        double x1 = (-b - sqrt(d) / 2);
        double x2 = (-b + sqrt(d) / 2);
        printf("x1=%lf, x2=%lf\n", x1,x2);
    }
}