#include <stdio.h>

int main() {
    FILE *file = fopen("/home/etryfly/Документы/Labs/2sem/KP7/testData.txt", "w");
    int n;
    int m;

    scanf("%d", &n);
    scanf("%d", &m);

    fwrite(&n, sizeof(int),1, file);
    fwrite(&m, sizeof(int),1, file);
    double data;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {

            scanf("%lf", &data);
            fwrite(&data, sizeof(data),1,file);
        }

    }
    }

