#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argv, char *argc[])
{
    char *var1 = getenv(argc[1]);
    char *var2 = getenv(argc[2]);

    if (var1 == NULL || var2 == NULL)
    {
        printf("0\n");
        return 0;
    }

    if (strlen(var1) == 0 || strlen(var2) == 0)
    {
        printf("0\n");
        return 0;
    }

    if (strcmp(var1, var2) == 0)
        printf("1\n");
    else
        printf("0\n");

    return 0;
}