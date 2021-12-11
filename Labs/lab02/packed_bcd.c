#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[])
{

    for (int arg = 1; arg < argc; arg++)
    {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value)
{
    uint32_t mask = packed_bcd_value & 0xFFFFFFFF; // unsigned forces 0-fill.
    uint32_t num = mask & 0xF;
    for (unsigned int i = 0, multiplier = 10; i < N_BCD_DIGITS; i++, multiplier *= 10)
    {
        mask >>= 4;
        num += (mask & 0xF) * multiplier;
    }

    return num;
}
