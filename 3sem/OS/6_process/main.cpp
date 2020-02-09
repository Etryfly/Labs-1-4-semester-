#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

using namespace std;

void rec(int c, int max, int it) {
    if (max == 0) return;
    pid_t pid = fork();
//    printf("pid=%d\n", pid);
    if (pid == -1) {
        printf("Error");
        return;
    }
    if (pid != 0) {
        if (c <= 0) {
            it++;
        max = rand() % --max;
//            max--;
            c = max;
            printf("Done\n");
        } else {
            c--;
        }


        printf("c = %d, maxC = %d, it = %d\n", c, max, it);
//    sleep(3);
        rec(c, max, it);
    }
}

int main() {

    srand(time(NULL));
    rec(6, 6, 0);
}