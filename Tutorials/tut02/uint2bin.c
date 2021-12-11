#include <stdio.h>

void uint2bin(unsigned int type)
{
    for (int i = sizeof(unsigned int) * 4; i >= 0; i--)
        if (type & (1 << i))
            printf("1");
        else
            printf("0");
    printf("\n");
}

int main(void)
{
    uint2bin(1);
    return 0;
}