


#include <stdio.h>
#include <stdlib.h>

void Split(int R, int A[], int q, FILE* fl)

{

    int last = R;

    if ( R == 0 ) {
        for (int j = 0; j < q; ++j) {
            printf("%d ", A[j]);
            fprintf(fl, "%d ", A[j]);
        }
        printf("\n");
        fprintf(fl, "\n");
    }

    else {

        if ( q > 0   &&  last > A[q-1] )

            last = A[q-1];

        for (int i = 1; i <= last; i ++ ) {

            A[q] = i;

            Split (R-i, A, q+1, fl);

        }

    }

}


int main() {
    int n;
    scanf("%d", &n);
    int A[n];
    char name[100] = "/home/etryfly/Документы/Labs/3sem/OS/3";
    snprintf(name, sizeof(name) + 10, "3-%d.txt", n);
    FILE* fl = NULL;
    if (!(fl = fopen(name, "w"))) {
        printf("Couldn't open file");
        exit(-1);
    }

    Split(n, A, 0, fl);
}