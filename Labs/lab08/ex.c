#include <stdio.h>

int hash(int n) { return (n % 7); }

int main(void)
{
    printf("%d %d\n", 10, hash(10)); // 3
    printf("%d %d\n", 5, hash(5));   // 5
    printf("%d %d\n", 7, hash(7));   // 0
    printf("%d %d\n", 3, hash(3));   // 3
    printf("%d %d\n", 14, hash(14)); // 0
    printf("%d %d\n", 12, hash(12)); // 5

    return 0;
}