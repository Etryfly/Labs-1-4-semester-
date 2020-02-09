


#include <stdio.h>

int main() {
    int l;
    int m;
    scanf("%d", &l);
    scanf("%d", &m);

    int a;
    int n;
    scanf("%d", &a);
    scanf("%d", &n);

    if (m != a) {
        printf("Can't multiply matrix");
        return 0;
    }
    int A[l][m];
    int B[m][n];
    for (int k = 0; k < l; ++k) {
        for (int i = 0; i < m; ++i) {
            scanf("%d", &A[k][i]);
        }
    }
    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &B[k][i]);
        }
    }


    int C[l][n];
    for (int i1 = 0; i1 < l; ++i1) {
        for (int i = 0; i < n; ++i) {
            C[i1][i] = 0;
        }
    }
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int r = 0; r < m; ++r) {
                C[i][j] += A[i][r] * B[r][j];
            }
        }
    }

    for (int j = 0; j < l; ++j) {
        for (int i = 0; i < n; ++i) {
            printf("%d ", C[j][i]);
        }
        printf("\n");
    }
}