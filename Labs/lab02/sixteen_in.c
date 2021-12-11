//
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16
#define CONTINUE 1

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[])
{

    for (int arg = 1; arg < argc; arg++)
    {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits)
{
    assert(strlen(bits) == N_BITS);
    int16_t num = 0;
    for (; *bits; num <<= 1, *bits++ == '1' ? num |= 1 : CONTINUE)
        // num <<= 1 == num *= 2
        // num |= 1 == num += 1
        ;
    return num;
}
