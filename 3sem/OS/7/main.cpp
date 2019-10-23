


#include <termio.h>
#include <cstring>
#include <cstdio>
#include <zconf.h>
#include <iostream>

using namespace std;
int main() {


    pid_t pid;
    char str[250] = "";
    char arg[250];
    while (1) {
        scanf("%s", str);
        if (strcmp(str, "STOP") == 0) exit(-1);
        scanf("%s", arg);

        switch (pid = fork()) {
            case -1:
                perror("fork");
                break;

            case 0: {
                if (strcmp(arg, "-") == 0) {
                    execlp(str, str, (char *) NULL);
                } else {
                    execlp(str, str, arg, NULL);
                    printf("%s", arg);
                }
                exit(-1);
            }
        }
    }

}