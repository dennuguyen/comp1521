// Compare 2 floats using bit operations only

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

// is negative
static int is_negative(float_components_t f)
{
    return f.sign == 1;
}

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2)
{
    float_components_t ieee1 = float_bits(bits1);
    float_components_t ieee2 = float_bits(bits2);

    // special 0 cases
    if (is_nan(ieee1) || is_nan(ieee2) ||
        is_positive_infinity(ieee1) || is_negative_infinity(ieee2) ||
        (is_zero(ieee1) && is_zero(ieee2)) ||
        (!is_negative(ieee1) && is_negative(ieee2)))
        return 0;

    // special 1 cases
    if (is_negative_infinity(ieee1) || is_positive_infinity(ieee2) ||
        (is_negative(ieee1) && !is_negative(ieee2)))
        return 1;

    // concurrently iterate through bits1 and bits2 and compares bits
    uint32_t a = is_negative(ieee1) && is_negative(ieee2) ? bits2 : bits1;
    uint32_t b = a == bits1 ? bits2 : bits1;
    for (int i = 31; i >= 0; i--)
    {
        // 1 bit is encountered first therefore must be larger than bits2
        if ((a >> i & 1) == 1 && (b >> i & 1) == 0)
            return 0;

        // 0 bit is encountered first therefore it must be smaller than bits2
        if ((a >> i & 1) == 0 && (b >> i & 1) == 1)
            return 1;
    }

    // bits1 and bits2 are the same
    return 0;
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
