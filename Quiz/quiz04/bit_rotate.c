#include "bit_rotate.h"

// Print bits
void print_bits(uint64_t value, int n_bits)
{
    for (int i = n_bits - 1; i >= 0; i--)
        printf("%ld", (value >> i) & 1);
    printf("\n");
}

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits)
{
    int n_bits = 8 * sizeof(bits);
    uint16_t rotated = 0;
    n_rotations %= n_bits; // consider n_rotations >= n_bits
    /**
     * -1 shift = 15 shift
     * -2 shift = 14 shift
     * -3 shift = 13 shift
     * ...
     * -15 shift = 1 shift
     */
    if (n_rotations < 0) // consider -ve n_rotations
        n_rotations += n_bits;

    for (int i = 0; i < n_bits; i++)
    {
        uint16_t bit = (bits >> i) & 1;
        rotated |= bit << ((i + n_rotations) % n_bits);
    }
    return rotated;
}
