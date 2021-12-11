#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[])
{
    if (argv != 2)
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argc[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argc[1]);
        exit(EXIT_FAILURE);
    }

    int c;
    for (long int i = 0; (c = fgetc(file)) != EOF; i++)
    {
        if (isprint(c))
            printf("byte %4ld: %3d 0x%02x '%c'\n", i, c, c, c);
        else
            printf("byte %4ld: %3d 0x%02x\n", i, c, c);
    }

    return EXIT_SUCCESS;
}
