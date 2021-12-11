#include <stdio.h>
#include <ctype.h>

int main(int argv, char *argc[])
{
    FILE *f = fopen(argc[1], "r");

    int sum = 0;
    int c = '\0';
    while ((c = getc(f)) != EOF)
    {
        if (isascii(c))
        {
            sum++;
        }
    }

    printf("%s contains %d ASCII bytes\n", argc[1], sum);

    return 0;
}