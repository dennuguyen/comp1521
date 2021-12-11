#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[])
{
    FILE *f1 = fopen(argc[1], "r");
    if (f1 == NULL)
    {
        fprintf(stderr, "ERROR: Could not open `%s`.\n", argc[1]);
        exit(EXIT_FAILURE);
    }

    FILE *f2 = fopen(argc[2], "r");
    if (f2 == NULL)
    {
        fprintf(stderr, "ERROR: Could not open `%s`.\n", argc[2]);
        exit(EXIT_FAILURE);
    }

    int c1 = fgetc(f1);
    int c2 = fgetc(f2);
    for (int i = 0; c1 != EOF && c2 != EOF; i++)
    {
        if (c1 != c2)
        {
            printf("Files differ at byte %d\n", i);
            return EXIT_SUCCESS;
        }

        if (!__isascii(c1))
        {
            printf("%s: byte %d is non-ASCII\n", argc[1], i);
            return EXIT_SUCCESS;
        }

        c1 = fgetc(f1);
        c2 = fgetc(f2);
    }

    if (c1 == EOF && c2 == EOF)
        printf("Files are identical\n");
    else if (c1 == EOF)
        printf("EOF on %s\n", argc[1]);
    else if (c2 == EOF)
        printf("EOF on %s\n", argc[2]);

    return EXIT_SUCCESS;
}