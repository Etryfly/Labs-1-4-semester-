


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <zconf.h>

//readDir

int main() {
    char name[6] = "out_";
    int file;
    int i = 0;
    name[4] = '0';
    char out2[6] = "out_";

    while ((file = open(name, O_CREAT | O_EXCL)) == -1) {
        name[4]++;
    }

    name[4]--;
    if (name[4] != 0) {
        out2[4] = (char) (name[4] + 1);
        link(name, out2);
    }





}