/**
 * Definitions of all useful bit functions and examinable bit functions.
 */

#include <stdint.h>

// Get nth bit
uint64_t get_nth_bit(uint64_t value, int n)
{
    return (value >> n) & 1;
}

// Print bits from MSB to LSB
void print_bits(uint64_t value, int n_bits)
{
    for (int i = n_bits - 1; i >= 0; i--)
    {
        int bit = (value >> i) & 1;
        printf("%d", bit);
    }
}

// Reverse the order of bits
uint64_t reverse_bits(uint64_t value)
{
    int n_bits = 8 * sizeof(value);
    uint64_t reversed = 0;
    for (int i = 0; i < n_bits; i++)
        reversed |= ((value >> i) & 1) << (n_bits - 1 - i);
    return reversed;
}

// return value with pairs of bits swapped between MSB and LSB pairs
uint64_t pair_swap(uint64_t value)
{
    int n_bits = 8 * sizeof(value);
    uint64_t reversed = 0;
    for (int i = 0; i < n_bits; i += 2)
    {
        uint64_t lb = (value >> (i + 1)) & 1;
        uint64_t rb = (value >> i) & 1;
        reversed |= lb << (n_bits - 1 - i);
        reversed |= rb << (n_bits - 1 - i - 1);
    }
    return reversed;
}

// return value with adjacent bits swapped, traversing from LSB to MSB
uint64_t adjacent_swap(uint64_t value)
{
    int n_bits = 8 * sizeof(value);
    uint64_t swap = 0;
    for (int i = 0; i < n_bits; i += 2)
    {
        uint64_t lb = (value >> (i + 1)) & 1;
        uint64_t rb = (value >> i) & 1;
        swap |= lb << i;
        swap |= rb << i + 1;
    }
    return swap;
}

// return value with bits rotated by n_rotations to the left
uint64_t bit_rotate(int n_rotations, uint64_t bits)
{
    int n_bits = 8 * sizeof(bits);
    uint64_t rotated = 0;
    n_rotations %= n_bits;
    if (n_rotations < 0)
        n_rotations += n_bits;

    for (int i = 0; i < n_bits; i++)
    {
        uint64_t bit = (bits >> i) & 1;
        rotated |= bit << ((i + n_rotations) % n_bits);
    }
    return rotated;
}

// return value with its sign flipped
uint64_t sign_flip(uint64_t value)
{
    int n_bits = 8 * sizeof(value);
    value ^= 1U << (n_bits - 1);
    return value;
}
