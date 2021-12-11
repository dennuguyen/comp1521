#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <xor-value>\n", argv[0]);
        return 1;
    }

    int xor_value = strtol(argv[1], NULL, 0);

    if (xor_value < 0 || xor_value > 255)
    {
        fprintf(stderr, "Usage: %s <xor-value>\n", argv[0]);
        return 1;
    }

    for (int xor_c, c; (c = getchar()) != EOF; putchar(xor_c))
        xor_c = c ^ xor_value;

    return 0;
}