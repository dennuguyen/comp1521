// Print out a float.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f)
{
    float_components_t ieee754 = (float_components_t){
        .sign = f >> 31,             // 10000000000000000000000000000000
        .exponent = (f >> 23) & 255, // 01111111100000000000000000000000
        .fraction = f & 8388607};    // 00000000011111111111111111111111

    return ieee754;
}

union bit2string {
    uint32_t bits;
    unsigned char string[sizeof(uint32_t)];
};

// is negative
static int is_negative(float_components_t f)
{
    return f.sign == 1;
}

//
// float_print is given the bits of a float as a uint32_t
// it prints out the float in the same format as "%.9g\n"
// using only putchar & puts
//
void float_print(uint32_t bits)
{
    float_components_t ieee = float_bits(bits);

    if (is_nan(ieee))
    {
        puts("nan");
        return;
    }

    if (is_positive_infinity(ieee))
    {
        puts("inf");
        return;
    }

    if (is_negative_infinity(ieee))
    {
        puts("-inf");
        return;
    }

    if (is_zero(ieee))
    {
        puts("0");
        return;
    }

    if (is_negative(ieee))
        putchar('-');

    // char num[32];
    // for (int i = 0; i < 32; i++)
    // {
    //     num[i] = (bits >> (i * 8)) & 0xFF;
    // }

    // char ch[32];
    // int n = sizeof bits;
    // for (int y = 0; n-- > 0; y++)
    //     ch[y] = ((bits >> (n * 8)) & 0xff) + '0';

    // union bit2string cell;
    // cell.bits = bits;
    // puts(cell.string);
    // puts(num);
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f)
{
    return f.sign == 0 && f.exponent == 255 && f.fraction == 4194304;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f)
{
    return f.sign == 0 && f.exponent == 255 && f.fraction == 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f)
{
    return f.sign == 1 && f.exponent == 255 && f.fraction == 0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f)
{
    return f.exponent == 0 && f.fraction == 0;
}
