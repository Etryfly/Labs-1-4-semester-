#include <stdio.h>

int get_count(int prev, int n) {
    if (0 == n)
        return 1;
    int count = 0;
    for (int level = 1; level < prev; ++level) {
        if ((n - level) < 0)
            break;
        count += get_count(level, n - level);
    }
    return count;
}

int main() {
    int n, count = 0;
    scanf("%d", &n);
    printf("%d", get_count(n+1, n));
}