#ifndef __COMMON__
#define __COMMON__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PRINTS

void print_int(const void *item)
{
    printf("%d", *(int *)item);
}

void print_ch(const void *item)
{
    printf("%s", (char *)item);
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

// UNLOADS

void unload(void *item)
{
    free(item);
}

// COMPARES

int compare_int(const void *item1, const void *item2)
{
    return *(int *)item1 == *(int *)item2 ? 0 : 1;
}

int compare_ch(const void *item1, const void *item2)
{
    return strcmp(item1, item2);
}

#endif /* __COMMON__ */