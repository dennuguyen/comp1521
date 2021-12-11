// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Print integer value in binary from MSB to LSB
void print_bits(uint64_t value, int n_bits)
{
    for (int i = n_bits - 1; i >= 0; i--)
        printf("%ld", (value >> i) & 1);
    printf("\n");
}

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value)
{
    int n_bits = 8 * sizeof(value);
    // print_bits(value, n_bits);
    uint64_t swap = 0;
    for (int i = 0; i < n_bits; i += 2)
    {
        uint64_t lb = (value >> (i + 1)) & 1;
        uint64_t rb = (value >> i) & 1;
        swap |= lb << i;
        swap |= rb << i + 1;
    }
    // print_bits(swap, n_bits);
    return swap;
}
