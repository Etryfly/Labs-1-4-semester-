#include <stdio.h>
const int N=1000;
int main(){

    int A[N][N];
    int num;
    int *p;
    while(1) {
        scanf("%d", &num);
        if (num == -1) break;
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                scanf("%d", &A[i][j]);
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
        if (num == 1) return 0;
        int nn = 0;
        while (nn != num - 1) {
            for (int i = num - 1; i >= num - 1 - nn; i -= 1) {
                for (int j = num - 1; j >= num - 1 - nn; j -= 1) {
                    if ((i - (num - 1 - nn)) + (j - (num - 1 - nn)) == nn) {
                        printf("%d ", A[i][j]);
                    }
                }
            }
            nn += 1;
        }


        for (int i = num - 1; i >= 0; i--) {
            printf("%d ", A[i][num - 1 - i]);
        }
        nn -= 1;

        while (nn >= 0) {
            for (int i = nn; i >= 0; i -= 1) {
                for (int j = nn; j >= 0; j -= 1) {
                    if ((i + j) == nn) {
                        printf("%d ", A[i][j]);
                    }
                }
            }
            nn -= 1;
        }
        printf("\n");
        printf("\n");
    }
}