#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argv, char *argc[])
{
    char *path = getenv("HOME");
    strncat(path, "/.diary", 8);
    FILE *f = fopen(path, "a");
    if (f == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argv; i++)
    {
        fputs(argc[i], f);
        fputc(' ', f);
    }
    fputc('\n', f);

    fclose(f);
    return EXIT_SUCCESS;
}
