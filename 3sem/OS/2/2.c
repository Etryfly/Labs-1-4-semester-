
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mn(int n) {

}

int main() {
    int n;
    scanf("%d", &n);
    char name[200] = "/home/etryfly/Документы/Labs/3sem/OS/2/2";
    snprintf(name, sizeof(name) + 10, "2-%d.txt", n);
    FILE* file;
    if (!(file = fopen(name, "w"))) {
        printf("Couldn't open file");
        exit(-1);
    }
    for(unsigned int mask=0,maxmask=1<<n; mask!=maxmask; ++mask)
    {
        for(unsigned int q=0; q<n; ++q)
            if(mask&(1<<q)) {
                printf("%d ", q + 1);
                fprintf(file, "%d ", q + 1);
            }

        printf("\n");
        fprintf(file, "\n");
    }
}