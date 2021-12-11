#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[])
{
    const char *out_file_name = "leave_only_ascii.tmp";

    FILE *in = fopen(argc[1], "r");
    if (in == NULL)
    {
        fprintf(stderr, "ERROR: Could not open `%s`.\n", argc[1]);
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(out_file_name, "w");
    if (out == NULL)
    {
        fprintf(stderr, "ERROR: Could not open `%s`.\n", argc[2]);
        exit(EXIT_FAILURE);
    }

    char c;
    for (int i = 0; (c = fgetc(in)) != EOF; i++)
    {
        if (!__isascii(c))
            continue;
        fputc(c, out);
    }

    remove(argc[1]);
    rename(out_file_name, argc[1]);

    return EXIT_SUCCESS;
}