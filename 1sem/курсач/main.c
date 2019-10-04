

#include <stdio.h>
#include <math.h>

double calc_eps() {
    double eps = 1.0;

    while (1.0 + eps > 1) {
        eps /= 2.0;
    }
    return eps;
}

double sqr(double x, int d) {
    double result = 1;
    for (int i = 0; i < d; ++i) {
        result*= x;
    }
    return result;
}

double calc_func(double x, double eps,int *i) {
    double down = 1.0;
    double up = x;
    double res = up/down;
    *i = 2;
    while (fabs(up/down) > eps) {
        if (*i == 100) {
            printf("It = 100, diff = %.20lf\n", fabs(log(1 + x -2*x*x)-res));
        }
        up = (sqr(2,*i)*sqr(-1,*i+1)-1)*sqr(x,*i);
        down = (double) *i;

        (*i)++;
        res += up/down;
    }

    return res;
}

int main() {
    double eps = calc_eps();
    printf("epsilon = %.30lf\n",eps);
    double res = 0;
    int it,*i = 0;
    i = &it;
    printf("|%10s|%25s|%25s|%25s|%4s\n","x","result","func in C lib","diff","it");

    for (double x = -0.2; x <= 0.3; x+= 0.05) {
        res = calc_func(x,eps,i);

        printf("|%*lf",10,x);
        printf("|%*.20lf",25,res);
        printf("|%*.20lf",25,log(1 + x -2*x*x));
        printf("|%*.20lf",25,fabs(log(1 + x -2*x*x)-res));
        printf("|%*d\n",4,*i);
    }

}