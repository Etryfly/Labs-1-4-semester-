


#include <dirent.h>
#include <stdio.h>
#include <zconf.h>
#include <memory.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int s, char** args) {
    DIR *dir;
    dir = opendir("./");

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        struct stat entryInfo;
        char buf[BUFSIZ] = {0};
        strcat(buf, "/home/etryfly/Документы/Labs/3sem/OS/fileCr/");
        strcat(buf, entry->d_name);



        FILE* file = fopen(buf, "r");

        fstat(fileno(file), &entryInfo);
        lstat(entry->d_name, &entryInfo);

        switch ( entryInfo.st_mode & S_IFMT ) {
            case S_IFDIR:
                printf("d");
                break;
            case S_IFCHR:
                printf("c");
                break;
            case S_IFBLK:
                printf("b");
                break;
            case S_IFREG:
                printf("-");
                break;
            case S_IFLNK:
                printf("l");
                break;
            case S_IFIFO:
                printf("p");
                break;
        }
        printf("%s", ((entryInfo.st_mode) & S_IRUSR ) ?  "r" : "-");
        printf("%s", ((entryInfo.st_mode) & S_IWUSR )  ?  "w" : "-");
        printf("%s", (((entryInfo.st_mode) & S_IXUSR)  ?  "x" : "-"));


        printf("%s", ((entryInfo.st_mode) & S_IRGRP ) ?  "r" : "-");
        printf("%s", ((entryInfo.st_mode) & S_IWGRP )  ?  "w" : "-");
        printf("%s", (((entryInfo.st_mode) & S_IXGRP)  ?  "x" : "-"));


        printf("%s", ((entryInfo.st_mode) & S_IROTH ) ?  "r" : "-");
        printf("%s", ((entryInfo.st_mode) & S_IWOTH )  ?  "w" : "-");
        printf("%s ", (((entryInfo.st_mode) & S_IXOTH)  ?  "x" : "-"));

        printf("%d ", (int) entryInfo.st_nlink);

        struct passwd *pw = getpwuid(entryInfo.st_uid);
        struct group  *gr = getgrgid(entryInfo.st_gid);

        printf("%s %s ", gr->gr_name, pw->pw_name);
        printf("%lld ",
               (long long) entryInfo.st_size);

        printf("%23s ", ctime(&entryInfo.st_mtim));


        printf("%s\n", entry->d_name);
        fclose(file);
    }

}