#include <stdlib.h>
#include <stdio.h>

int max(int a, int b) {
    return (a>b) ? a : b;
}

int min(int a, int b) {
    return (a<b) ? a:b;
}

int sign(int x) {
    if (x < 0) return -1;
    return (x>0) ? 1 : 0;
}

int d(int a,int b) {
    return (a*b>=0) ? a/b : a/b-1;
}
int mod(int a,int b) {
    return a - d(a,b)*b;
}

int main() {
    int x,y,r1,r2,i,j,l,i0,j0,l0,m;
    double c; //r1 - внутренний радиус, r2 - внешний
    i0=i=26;
    j0=j=8;
    l0=l=-3;

    for (int k = 1; k < 51; ++k) {
        i = mod(min(i0+j0,i0+l0)*(k+1),30);
        j=j0+mod(l0*sign(j0),20)+mod(k*sign(i0),10);
        m = max(i0*j0,i0*l0);
        m = max(m, j0*l0);
        l=mod(m,30);
        i0=i;
        j0=j;
        l0=l;
        x=i;
        y=j;
        c = (x+10)*(x + 10) + (y + 10)*(y + 10);
        if (c > r1*r1 && c < r2*r2) {
            printf(" YES k=%d x=%d y=%d l=%d\n",k,x,y,l);
            return 0;
        }
    }

    printf(" NO x=%d y=%d l=%d\n",x,y,l);
}