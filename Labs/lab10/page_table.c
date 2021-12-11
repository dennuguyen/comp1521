// Simulate LRU replacement of page frames
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// represent an entry in a simple inverted page table
typedef struct ipt_entry
{
    int virtual_page; // -1 if physical page free
    int last_access_time;
    bool read;
    bool write;
} ipt_entry_t;

// Return true if permission are valid
bool can_access(char action, ipt_entry_t ipt)
{
    switch (action)
    {
    case 'r':
        printf(" - read access - ");
        if (ipt.read == false)
        {
            printf("illegal\n");
            return false;
        }
        break;
    case 'w':
        printf(" - write access - ");
        if (ipt.write == false)
        {
            printf("illegal\n");
            return false;
        }
        break;
    // default:
    //     fprintf(stderr, "This should be impossible.\n");
    //     exit(EXIT_FAILURE);
    }

    return true;
}

void access_page(char action, int virtual_page, int access_time, int n_physical_pages, struct ipt_entry *ipt)
{
    printf("Time %d: virtual page %d ", access_time, virtual_page);

    // The virtual page is already in a physical page
    for (int i = 0; i < n_physical_pages; i++)
        if (ipt[i].virtual_page == virtual_page)
        {
            switch (action)
            {
            case 'R':
                printf("mapped read-only\n");
                ipt[i].read = true;
                return;
            case 'W':
                printf("mapped read-write\n");
                ipt[i].read = true;
                ipt[i].write = true;
                return;
            case 'U':
                printf("unmapped - physical page %d now free\n", i);
                ipt[i].read = false;
                ipt[i].write = false;
                ipt[i].virtual_page = -1;
                ipt[i].last_access_time = -1;
                return;
            }
            if (can_access(action, ipt[i]) == false)
                return;
            printf("at physical page %d\n", i);
            ipt[i].last_access_time = access_time;
            return;
        }

    // The virtual page is not in a physical page and there is free physical page
    for (int i = 0; i < n_physical_pages; i++)
        if (ipt[i].virtual_page == -1)
        {
            switch (action)
            {
            case 'R':
                printf("mapped read-only\n");
                ipt[i].read = true;
                return;
            case 'W':
                printf("mapped read-write\n");
                ipt[i].read = true;
                ipt[i].write = true;
                return;
            case 'U':
                printf("unmapped\n");
                ipt[i].read = false;
                ipt[i].write = false;
                return;
            }
            if (can_access(action, ipt[i]) == false)
                return;
            printf("loaded to physical page %d\n", i);
            ipt[i].virtual_page = virtual_page;
            ipt[i].last_access_time = access_time;
            return;
        }

    // The virtual page is not in a physical page and there is no free physical page
    int oldest_page = virtual_page;
    int oldest_time = access_time;
    for (int i = 0; i < n_physical_pages; i++)
        if (ipt[i].last_access_time < oldest_time)
        {
            oldest_page = i;
            oldest_time = ipt[i].last_access_time;
        }

    if (can_access(action, ipt[oldest_page]) == false)
        return;

    printf(" - virtual page %d evicted - ", ipt[oldest_page].virtual_page);
    ipt[oldest_page].virtual_page = -1;
    ipt[oldest_page].last_access_time = -1;

    printf("loaded to physical page %d\n", oldest_page);
    ipt[oldest_page].virtual_page = virtual_page;
    ipt[oldest_page].last_access_time = access_time;
    return;
}


void lru(int n_physical_pages, int n_virtual_pages)
{
    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n",
        n_physical_pages, n_virtual_pages);
    struct ipt_entry *ipt = malloc(n_physical_pages * sizeof(struct ipt_entry));
    assert(ipt);

    for (int i = 0; i < n_physical_pages; i++)
    {
        ipt[i].virtual_page = -1;
        ipt[i].last_access_time = -1;
        ipt[i].read = false;
        ipt[i].write = false;
    }

    char c;
    int virtual_page;
    for (int access_time = 0; scanf(" %c %d", &c, &virtual_page) == 2; access_time++)
    {
        assert(c == 'R' || c == 'W' || c == 'U' || c == 'r' || c == 'w');
        assert(0 <= virtual_page && virtual_page < n_virtual_pages);
        access_page(c, virtual_page, access_time, n_physical_pages, ipt);
    }
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <n-physical-pages> <n-virtual-pages>\n", argv[0]);
        return 1;
    }
    lru(atoi(argv[1]), atoi(argv[2]));
    return 0;
}
