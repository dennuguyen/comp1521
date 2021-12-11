#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argv, char *argc[])
{
    FILE *f = fopen(argc[1], "r");

    int sum = 0;
    while (1)
    {
        int byte1 = fgetc(f);
        if (byte1 == EOF) break;
        if (((byte1 >> 7) & 0b1) == 0b1)
        {
            sum++;
            continue;
        }

        int byte2 = fgetc(f);
        if (byte2 == EOF) break;
        if ((((byte1 >> 5) & 0b111) == 0b110) &&
            (((byte2 >> 6) & 0b11) == 0b10))
        {
            sum++;
            continue;
        }

        int byte3 = fgetc(f);
        if (byte3 == EOF) break;
        if ((((byte1 >> 4) & 0b1111) == 0b1110) &&
            (((byte2 >> 6) & 0b11) == 0b10) &&
            (((byte3 >> 6) & 0b11) == 0b10))
        {
            sum++;
            continue;
        }

        int byte4 = fgetc(f);
        if (byte4 == EOF) break;
        if ((((byte1 >> 3) & 0b11111) == 0b11110) &&
            (((byte2 >> 6) & 0b11) == 0b10) &&
            (((byte3 >> 6) & 0b11) == 0b10) &&
            (((byte4 >> 6) & 0b11) == 0b10))
        {
            sum++;
            continue;
        }

        // printf("%s: invalid UTF-8 after %d valid UTF-8 characters\n", argc[1], sum);
        // exit(0);
    }

    printf("%s: %d UTF-8 characters\n", argc[1], sum);
    return 0;
}