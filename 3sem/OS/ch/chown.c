#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <zconf.h>

int main(int argc, char* argv[]) {
    uid_t uid;
    struct passwd *pwd;
    pwd = getpwnam(argv[1]);
    uid = pwd->pw_uid;
    printf("%s %d\n", pwd->pw_name, uid);
    if (chown(argv[2], uid, uid) == -1) {
        perror("chown");
    }
}