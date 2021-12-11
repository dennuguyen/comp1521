#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argv, char *argc[])
{
    char *path = getenv("HOME");
    strncat(path, "/.diary", 8);

    struct stat st;
    if (stat(path, &st) != 0)
    {
        printf("0\n");
        return EXIT_FAILURE;
    }

    int r1 = st.st_mode & S_IRUSR;
    int r2 = st.st_mode & S_IRGRP;
    int r3 = st.st_mode & S_IROTH;

    if (r1 && r2 && r3)
        printf("1\n");
    else
        printf("0\n");

    return EXIT_SUCCESS;
}
