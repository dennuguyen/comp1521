// Multiply a float by 2048 using bit operations only

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

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -int, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f)
{
    float_components_t ieee754 = float_bits(f);

    if (is_nan(ieee754) || is_positive_infinity(ieee754) ||
        is_negative_infinity(ieee754) || is_zero(ieee754))
        return f;

    // must look ahead for overflow
    for (int i = 0; i < 11; i++)
    {
        if (ieee754.exponent + 1 >= 255)
        {
            ieee754.exponent = 255;
            ieee754.fraction = 0;
            break;
        }
        else
            ieee754.exponent += 1;
    }

    return (ieee754.sign << 31) |
           (ieee754.exponent << 23) | (ieee754.fraction);
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
