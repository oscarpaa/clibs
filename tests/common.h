#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _token_t
{
    char *name;
    size_t index;
    size_t type;
} token_t;

// PRINTS

void print_int(const void *item)
{
    printf("%d", *(int *)item);
}

void print_c(const void *item)
{
    printf("%c", *(char *)item);
}

void print_ch(const void *item)
{
    printf("%s", (char *)item);
}

void print_tok(const void *item)
{
    printf("{%s, ", ((token_t *)item)->name);
    printf("%d, ", ((token_t *)item)->index);
    printf("%d}", ((token_t *)item)->type);
}

// LOADS

void load_int(const void *item, void **new_item)
{
    size_t len = sizeof(int);
    *new_item = malloc(len);
    memcpy(*new_item, item, len);
}

void load_ch(const void *item, void **new_item)
{
    size_t len = strlen((char *)item) + 1;
    *new_item = malloc(len);
    memcpy(*new_item, item, len);
}

void load_tok(const void *item, void **new_item)
{
    size_t len = sizeof(token_t);
    size_t len_n = strlen(((token_t *)item)->name) + 1;

    *new_item = malloc(len);
    memcpy(*new_item, item, len);

    ((token_t *)*new_item)->name = malloc(len_n);
    memcpy(*new_item, item, len);
}

// UNLOADS

void unload(void *item)
{
    free(item);
}

void unload_tok(void *item)
{
    free(((token_t *)item)->name);
    free(item);
}

// COMPARES

int compare_int(const void *item1, const void *item2)
{
    return *(int *)item1 != *(int *)item2;
}

int compare_ch(const void *item1, const void *item2)
{
    return strcmp(item1, item2);
}

#endif /* __COMMON__ */