#include <stdio.h>

char in[100], C[100], D[100];
int i = 0, k = 0, Count = 1;
int B[100] = {0};

void F () {
    if (k == i) {
        int flag = 1, c = 0;
        for (int a = 0; a < i; a++) {
            if (D[a] > C[a]) {
                flag = 0;
                break;
            }
            if (D[a] < C[a])
                break;
            if (D[a] == C[a])
                c++;
        }
        if (c == i) flag = 0;
        if (flag) {
            printf("%d) ", Count);
            Count++;
            for (int a = 0; a < i; a++)
                printf("%c", C[a]);
            printf("\n");
            for (int a = 0; a < i; a++)
                D[a] = C[a];
        }
        return;
    }
    for (int j = 0; j < i; j++) {
        if (!B[j]) {
            C[k] = in[j];
            B[j] = 1;
            k++;
            F();
            k--;
            B[j] = 0;
        }
    }
    return;
}

int main() {

    int n;
    char ch;
    ch = getchar();
    while (ch != '\n') {
        in[i++] = ch;
        ch = getchar();
    }

    for (int a = 0; a < i; a++) {
        for (int b = a+1; b < i; b++) {
            if (in[a] > in[b]) {
                ch = in[a];
                in[a] = in[b];
                in[b] = ch;
            }
        }
    }
    printf("%d) ", Count); Count++;
    for (int a = 0; a < i; a++) {
        D[a] = in[a];
        printf("%c", in[a]);
    }
    printf("\n");
    F();
}
