#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[])
{
    if (argv < 2)
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argc[1], "w");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argc[1]);
        exit(EXIT_FAILURE);
    }

    for (int i = 2; argc[i] != NULL; i++)
        fputc(atoi(argc[i]), file);

    return EXIT_SUCCESS;
}
