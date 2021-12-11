#include <ctype.h>
#include <stdbool.h>
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

    for (int c = EOF, newline = false; (c = fgetc(file)) != EOF; newline = false)
    {
        char buffer[4];
        for (int i = 0; c != EOF && isprint(c); i++, c = fgetc(file))
        {
            if (i < 3)
                buffer[i] = c;
            else if (i == 3)
            {
                buffer[i] = '\0';
                printf("%s", buffer);
                printf("%c", c);
                newline = true;
            }
            else if (i > 3)
                printf("%c", c);
        }

        if (newline == true)
            printf("\n");
    }

    return EXIT_SUCCESS;
}
