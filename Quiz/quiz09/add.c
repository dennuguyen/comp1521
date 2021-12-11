#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// Print bits from MSB to LSB
void print_bits(uint64_t value, int n_bits)
{
    for (int i = n_bits - 1; i >= 0; i--)
    {
        int bit = (value >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}
// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t)
{
    unsigned int result = 0b100000;
    result |= (d << 11);
    result |= (t << 16);
    result |= (s << 21);
    return result;
}
