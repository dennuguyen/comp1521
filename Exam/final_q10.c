#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <sys/stat.h>

int main(int argv, char *argc[])
{
    char *file = argc[1];
    char *dir = NULL;

    if (argv == 3)
    {
        dir = argc[2];
    }

    if (argv == 2)
    {
        dir = ".";
    }

    FILE *f = fopen(file, "w");

    // parse thru each folder
    {
        printf("%s:\n", file);

        // parse thru each file
        {
            struct stat st;
            stat(file, &st);
            printf((S_ISDIR(st.st_mode)) ? "d" : "-");
            printf((st.st_mode & S_IRUSR) ? "r" : "-");
            printf((st.st_mode & S_IWUSR) ? "w" : "-");
            printf((st.st_mode & S_IXUSR) ? "x" : "-");
            printf((st.st_mode & S_IRGRP) ? "r" : "-");
            printf((st.st_mode & S_IWGRP) ? "w" : "-");
            printf((st.st_mode & S_IXGRP) ? "x" : "-");
            printf((st.st_mode & S_IROTH) ? "r" : "-");
            printf((st.st_mode & S_IWOTH) ? "w" : "-");
            printf((st.st_mode & S_IXOTH) ? "x" : "-");
            printf("%lu ", st.st_nlink);
            printf("%s ", getgrgid(st.st_gid)->gr_name);
            printf("%s ", getpwuid(st.st_uid)->pw_name);
            char *time = ctime(&st.st_mtime);
            printf("%s ", time);
            printf("%s\n", file);
        }
    }

    fclose(f);
    return 0;
}