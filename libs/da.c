#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "da.h"

void da_create(da_t **arr)
{
    assert(*arr == NULL);

    *arr = malloc(sizeof(da_t));
    (**arr).items = NULL;
    (**arr).length = 0;
    (**arr).capacity = 0;
}

void da_destroy(da_t **arr)
{
    assert(*arr != NULL);

    free(*arr);
    *arr = NULL;
}

void da_append_back(da_t *arr, const void *item, size_t size_item)
{
    assert(arr != NULL);

    if (arr->length == arr->capacity)
    {
        if (arr->capacity == 0)
        {
            arr->capacity = DA_INIT_CAP;
        }
        else
        {
            arr->capacity += DA_INIT_CAP;
        }
        arr->items = realloc(arr->items, arr->capacity * size_item);
        memset(arr->items + arr->length * size_item, 0, DA_INIT_CAP * size_item);
    }
    memcpy(arr->items + (arr->length * size_item), item, size_item);
    arr->length++;
}

void da_resize(da_t *arr, size_t new_size, size_t size_item)
{
    assert(arr != NULL);

    arr->items = realloc(arr->items, new_size * size_item);

    if (arr->capacity < new_size)
    {
        memset(arr->items + arr->capacity * size_item, 0, (new_size - arr->capacity) * size_item);
    }

    arr->capacity = new_size;
    arr->length = arr->length < arr->capacity ? arr->length : arr->capacity;
}

size_t da_size(const da_t *arr)
{
    assert(arr != NULL);

    return arr->length;
}

size_t da_capacity(const da_t *arr)
{
    assert(arr != NULL);

    return arr->capacity;
}

void da_print(const da_t *arr, size_t size_item, void (*print_func)(const void *))
{
    assert(arr != NULL);

    printf("[");

    void *ptr = arr->items;

    for (size_t i = 0; i < arr->length; i++)
    {
        print_func(ptr);
        if (i < arr->length - 1)
        {
            printf(", ");
        }
        ptr += size_item;
    }

    printf("]\n");
}