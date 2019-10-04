#include <sys/stat.h>
#include <memory.h>


int main(int s, char** args) {
    mode_t flag = 0;

    switch (args[1][0]) {
        case '7':
            flag |= S_IRUSR | S_IWUSR | S_IXUSR;
            break;

        case '6':
            flag |= S_IRUSR | S_IWUSR;
            break;

        case '5':
            flag |= S_IRUSR | S_IXUSR;
            break;

        case '4':
            flag |= S_IRUSR;
            break;
    }


    switch (args[1][1]) {
        case '7':
            flag |= S_IRGRP | S_IWGRP | S_IXGRP;
            break;

        case '6':
            flag |= S_IRGRP | S_IWGRP;
            break;

        case '5':
            flag |= S_IRGRP | S_IXGRP;
            break;

        case '4':
            flag |= S_IRGRP;
            break;
    }


    switch (args[1][2]) {
        case '7':
            flag |= S_IROTH | S_IWOTH | S_IXOTH;
            break;

        case '6':
            flag |= S_IROTH | S_IWOTH;
            break;

        case '5':
            flag |= S_IROTH | S_IXOTH;
            break;

        case '4':
            flag |= S_IROTH;
            break;
    }

    chmod(args[2], flag);
}