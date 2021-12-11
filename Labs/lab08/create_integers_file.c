#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[])
{
    if (argv != 4)
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

    for (int i = atoi(argc[2]); i <= atoi(argc[3]); i++)
        fprintf(file, "%d\n", i);

    return EXIT_SUCCESS;
}
