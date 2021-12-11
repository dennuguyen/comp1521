// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value)
{
    return ((value & 0x000F) << 8) | ((value & 0x00F0) << 8) |
           ((value & 0x0F00) >> 8) | ((value & 0xF000) >> 8);
}
