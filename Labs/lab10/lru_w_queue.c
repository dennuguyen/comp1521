#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Page
{
    int physical; // value
    struct Page *prev;
    struct Page *next;
} Page;

typedef struct Queue
{
    Page *head;
    Page *tail;
} Queue;

typedef struct HashTable
{
    int size;
    int max;
    Queue *page_list; // queue of physical pages
    Page **pages;     // array of physical pages
} HashTable;

Page *new_page(int page)
{
    Page *p = malloc(sizeof(Page));
    if (p == NULL)
    {
        fprintf(stderr, "Could not malloc Page.\n");
        exit(EXIT_FAILURE);
    }
    p->physical = page;
    p->prev = p->next = NULL;
    return p;
}

// void free_page(Page *p)
// {
//     free(p);
//     p = NULL;
// }

Queue *new_queue(int max)
{
    Queue *q = malloc(max * sizeof(Queue));
    if (q == NULL)
    {
        fprintf(stderr, "Could not malloc Queue.\n");
        exit(EXIT_FAILURE);
    }
    q->head = q->tail = NULL;
    return q;
}

// void free_queue(Queue *q)
// {
//     if (q == NULL)
//         return;
//     for (Page *curr = q->head, *next; curr != NULL;)
//     {
//         next = curr->next;
//         free_page(curr);
//         curr = next;
//     }
//     free(q);
//     q = NULL;
// }

HashTable *new_hashtable(int max)
{
    HashTable *ht = malloc(sizeof(HashTable));
    if (ht == NULL)
    {
        fprintf(stderr, "Could not malloc HashTable.\n");
        exit(EXIT_FAILURE);
    }
    ht->size = 0;
    ht->max = max;
    ht->page_list = new_queue(max);
    ht->pages = malloc(max * sizeof(Page));
    for (int i = 0; i < max; i++)
        ht->pages[i] = NULL;
    return ht;
}

// void *free_hashtable(HashTable *ht)
// {
//     free_queue(ht->page_list);
//     for (int i = 0; i < ht->max; i++)
//         free_page(ht->pages[i]);
//     free(ht);
//     ht = NULL;
// }

void enqueue(Queue *q, int page)
{
    if (q == NULL)
        return;

    Page *p = new_page(page);
    if (q->head == NULL)
        q->head = p;
    if (q->tail != NULL)
        q->tail->next = p;
    q->tail = p;
}

void dequeue(Queue *q)
{
    if (q == NULL || q->head == NULL)
        return;

    Page *tmp = q->head;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;
    free(tmp);
    tmp = NULL;
}

void show_queue(Queue *q)
{
    if (q == NULL || q->head == NULL)
        return;

    printf("[");
    for (Page *curr = q->head; curr != NULL; curr = curr->next)
    {
        if (curr->next == NULL)
            printf("%d", curr->physical);
        else
            printf("%d, ", curr->physical);
    }
    printf("]\n");
}

void load_page(HashTable *ht, int page)
{
    printf("virtual page %d ", page);

    // virtual page is not loaded in physical page
    if (ht->pages[page] == NULL)
    {
        ht->pages[page] = new_page(page);

        // no free physical page
        if (ht->size == ht->max)
        {
            printf("- virtual page %d evicted - ", ht->page_list->head->physical);
            ht->pages[ht->page_list->head->physical] = NULL;
            dequeue(ht->page_list);
            ht->size--;
        }
        printf("loaded to physical page %d", ht->size);
        enqueue(ht->page_list, page);
        ht->size++;
    }
    // virtual page is already loaded in physical page
    else
    {
        printf("-> physical page %d", ht->pages[page]->physical);
        ht->page_list->head->prev = ht->pages[page];   // head prev ptr to page
        ht->page_list->head = ht->pages[page];         // set page as head
        ht->pages[page]->prev = ht->pages[page]->next; // remove page from list
    }
}

int main(int argv, char *argc[])
{
    if (argv != 3)
    {
        fprintf(stderr, "Incorrect number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    printf("Simulating %d pages of physical memory, %d pages of virtual memory\n", atoi(argc[1]), atoi(argc[2]));
    HashTable *ht = new_hashtable(atoi(argc[1]));

    for (int i = 0, page; scanf("%d", &page) == 1;)
    {
        printf("Time %d: ", i++);
        load_page(ht, page);
        printf("\n");
        show_queue(ht->page_list);
    }

    return EXIT_SUCCESS;
}
