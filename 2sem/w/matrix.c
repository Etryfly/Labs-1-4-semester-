


#include <stdio.h>

int main() {
    char* file = "/home/etryfly/Документы/Labs/2sem/w/matrix";
    FILE* f = fopen(file, "r");
    int n;
    int m;
    scanf("%d", &n);
    scanf("%d", &m);
    int arr[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fscanf(f, "%d", &arr[j][i]);
        }

    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < m; ++i) {
            printf("%d ", arr[k][i]);
        }
        printf("\n");
    }
}