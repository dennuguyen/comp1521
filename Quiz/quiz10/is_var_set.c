#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argv, char *argc[])
{
    if (getenv(argc[1]) && strlen(getenv(argc[1])) != 0)
        printf("1\n");
    else
        printf("0\n");

    return EXIT_SUCCESS;
}
