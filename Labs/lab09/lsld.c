#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // No given files so give current directory
    if (argc == 1)
    {
        argc = 2;
        argv[1] = ".";
    }

    int n_gr_name = 0;
    int n_pw_name = 0;
    int n_size = 0;

    // First parse to get format
    for (int i = 1; i < argc; i++)
    {
        struct stat st;
        stat(argv[i], &st);

        // Get max length for group name
        char *gr_name = getgrgid(st.st_gid)->gr_name;
        n_gr_name = strlen(gr_name) > n_gr_name ? strlen(gr_name) : n_gr_name;

        // Get max length for user name
        char *pw_name = getpwuid(st.st_uid)->pw_name;
        n_pw_name = strlen(pw_name) > n_pw_name ? strlen(pw_name) : n_pw_name;

        // Get max length for file size
        char size[256];
        snprintf(size, 256, "%ld", st.st_size);
        n_size = strlen(size) > n_size ? strlen(size) : n_size;
    }

    // Second parse to print everything
    for (int i = 1; i < argc; i++)
    {
        struct stat st;
        stat(argv[i], &st);

        // Permissions
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
        printf(" ");

        // Hard link count
        printf("%lu ", st.st_nlink);

        // Group name
        printf("%-*s ", n_gr_name, getgrgid(st.st_gid)->gr_name);

        // User name
        printf("%-*s ", n_pw_name, getpwuid(st.st_uid)->pw_name);

        // Size
        printf("%*ld ", n_size, st.st_size);

        // ctime gives mostly correct format
        char *time = ctime(&st.st_mtime);
        time += 4;                     // strip month
        time[strlen(time) - 9] = '\0'; // strip year

        // Time
        printf("%s ", time);

        // File name
        printf("%s\n", argv[i]);
    }

    return EXIT_SUCCESS;
}
