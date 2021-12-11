/**
 * COMP1521 compilation of useful C stuff.
 */

/**
 * Bit Masking.
 */

#include <stdint.h>

uint8_t AND(uint8_t mask, uint8_t value)
{
    return mask & value;
}

uint8_t XOR(uint8_t mask, uint8_t value)
{
    return mask ^ value;
}

uint8_t OR(uint8_t mask, uint8_t value)
{
    return mask | value;
}

uint8_t ODD(uint8_t i)
{
    return i & 1;
}

/**
 * Bit Fields.
 */
struct example
{
    unsigned int a : 3; // 3 bits
    unsigned int b : 2; // 2 bits
};                      // 8 bit number: xxxb baaa

/**
 * C Lambda.
 */

#define lambda(return_type, function_body) \
    ({return_type fn function_body fn})

lambda(
    int, (int x, int y) { return x > y; })(1, 2);

/**
 * Finite State Machine implemenation using macros.
 * 
 */
// #define FSM
// #define STATE(x) s_##x:
// #define NEXTSTATE(x) goto s_##x

// FSM
// {
//     STATE(x)
//     {
//         ... NEXTSTATE(y);
//     }

//     STATE(y)
//     {
//         ... if (x == 0)
//             NEXTSTATE(y);
//         else NEXTSTATE(x);
//     }
// }

#include <stdio.h>

int main()
{
    int a = 3;
    float b = 6.412355;
    printf("%.*f\n", a, b);
    return 0;
}