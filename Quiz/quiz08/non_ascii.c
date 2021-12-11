#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[])
{
    FILE *f = fopen(argc[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "ERROR: Could not open `%s`.\n", argc[1]);
        exit(EXIT_FAILURE);
    }

    char c;
    for (int i = 0; (c = fgetc(f)) != EOF; i++)
        if (!__isascii(c))
        {
            printf("%s: byte %d is non-ASCII\n", argc[1], i);
            return EXIT_SUCCESS;
        }

    printf("%s is all ASCII\n", argc[1]);
    return EXIT_SUCCESS;
}