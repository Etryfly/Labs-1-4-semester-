#include <stdio.h>
#include <stdlib.h>

typedef struct _s {
  int value;
} S;

S binary_search(int val, S* arr, int size) {
    int i = size/2;
    int c = arr[i].value;

    while (c != val) {
        if (c > val) {
            i = i/2;
        } else {
            i+= i/2;
        }
        c = arr[i].value;
    }
    return arr[i];
}

int main() {
    int size;
    S arr[size];
    scanf("%d",&size);
    for (int i = 0; i < size; ++i) {
        int val;
        scanf("%d", &val);
        S s;
        s.value = val;
        arr[i] = s;
    }
   
    printf("%d", binary_search(0, arr, size).value);
}