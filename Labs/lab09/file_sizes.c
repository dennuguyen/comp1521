#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    long total = 0;

    for (int i = 1; i < argc; i++)
    {
        struct stat st;
        stat(argv[i], &st);
        printf("%s: %ld bytes\n", argv[i], st.st_size);
        total += st.st_size;
    }

    printf("Total: %ld bytes\n", total);

    return EXIT_SUCCESS;
}
