#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argv, char *argc[])
{
    struct stat file;
    if (stat(argc[1], &file) == 0 && S_ISDIR(file.st_mode))
        printf("1\n");
    else
        printf("0\n");

    return EXIT_SUCCESS;
}
