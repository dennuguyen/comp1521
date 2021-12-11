// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>

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
