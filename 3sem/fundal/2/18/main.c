


#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    double arr[n][n];

    for (int l = 0; l < n; ++l) {
        for (int i = 0; i < n; ++i) {
            scanf("%lf", &arr[l][i]);
        }
    }

    for (int k = 0; k < n; k ++)
    {
        for (int i = k + 1; i < n; i ++)
        {
            double mu = arr[i][k] / arr[k][k];
            for (int j = 0; j < n; j ++)
                arr[i][j] -= arr[k][j] * mu;
        }
    }

//
//    for (int m = 0; m < n; ++m) {
//        for (int i = 0; i < n; ++i) {
//            printf("%lf ", arr[m][i]);
//        }
//        printf("\n");
//    }

    double det = arr[0][0];

    for (int i = 1; i < n; ++i) {
        det*= arr[i][i];
    }
    if (isnan(det)) printf("0");
    else printf("%lf\n", det);
}