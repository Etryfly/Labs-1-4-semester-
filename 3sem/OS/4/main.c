#include <stdio.h>

char A[10], C[10], D[10];
int i = 0, k = 0, Count = 1;
int B[10] = {0};

void F () {
    if (k == i) {
        int flag = 1, c = 0;
        for (int a = 0; a < i; a++) {
            if (D[a] > C[a]) {flag = 0; break;}
            if (D[a] < C[a]) break;
            if (D[a] == C[a]) c++;
        }
        if (c == i) flag = 0;
        if (flag) {
            printf("%d) ", Count); Count++;
            for (int a = 0; a < i; a++) printf("%c", C[a]);
            printf("\n");
            for (int a = 0; a < i; a++) D[a] = C[a];
        }
        return;
    }
    for (int j = 0; j < i; j++) {
        if (!B[j]) {
            C[k] = A[j];
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
        A[i++] = ch;
        ch = getchar();
    }
    for (int a = 0; a < i; a++) {
        for (int b = a+1; b < i; b++) {
            if (A[a] > A[b]) {
                ch = A[a];
                A[a] = A[b];
                A[b] = ch;
            }
        }
    }
    printf("%d) ", Count); Count++;
    for (int a = 0; a < i; a++) {D[a] = A[a]; printf("%c", A[a]);}
    printf("\n");
    F();

}
