#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "da.h"

void da_create(da_t **arr, size_t init_cap)
{
    assert(*arr == NULL);
    assert(init_cap);

    *arr = malloc(sizeof(da_t));
    (**arr).items = malloc(init_cap * sizeof(void *));
    (**arr).length = 0;
    (**arr).capacity = init_cap;
}

void da_destroy(da_t **arr)
{
    assert(*arr != NULL);
    assert(!(**arr).length);

    (**arr).capacity = 0;

    free((**arr).items);
    free(*arr);
    *arr = NULL;
    
}

void da_clear(da_t *arr, void (*unload_fun)(void *))
{
    assert(arr != NULL);
    assert(arr->length);

    for (size_t i = 0; i < arr->length; i++)
    {
        unload_fun(arr->items[i]);
    }
    arr->length = 0;
}

void da_delete(da_t *arr, void (*unload_fun)(void *))
{
    assert(arr != NULL);
    assert(arr->length);

    unload_fun(arr->items[--arr->length]);
}

size_t da_get_index(const da_t *arr, const void *item, int (*cmp_fun)(const void *, const void *))
{
    assert(arr != NULL);
    assert(item != NULL);

    int find = 0;
    size_t index = 0;
    while (index < arr->length && !find)
    {
        if (!cmp_fun(item, arr->items[index]))
        {
            find = 1;
        }
        else
        {
            index++;
        }
    }
    return index;
}

void da_append(da_t *arr, const void *item, void (*load_fun)(const void *, void **))
{
    assert(arr != NULL);
    assert(item != NULL);

    if (arr->length == arr->capacity)
    {
        arr->capacity *= 2;
        arr->items = realloc(arr->items, arr->capacity * sizeof(void *));
    }
    load_fun(item, &arr->items[arr->length]);
    arr->length++;
}

void da_append_array(da_t *arr, void (*load_fun)(const void *, void **), size_t count, void *arr_items[])
{
    assert(arr != NULL);
    assert(arr_items != NULL);
    assert(count);

    for (size_t i = 0; i < count; i++)
    {
        da_append(arr, arr_items[i], load_fun);
    }
}

void da_append_block(da_t *arr, void (*load_fun)(const void *, void **), size_t count, ...)
{
    assert(arr != NULL);
    assert(count);

    va_list ap;
    va_start(ap, count);

    void *item;

    for (size_t i = 0; i < count; i++)
    {
        item = va_arg(ap, void *);
        da_append(arr, item, load_fun);
    }

    va_end(ap);
}

void *da_get_at(const da_t *arr, size_t index)
{
    assert(arr != NULL);
    assert(index < arr->length);

    return arr->items[index];
}

void da_set_at(da_t *arr, size_t index, const void *item, void (*unload_fun)(void *), void (*load_fun)(const void *, void **))
{
    assert(arr != NULL);
    assert(index <= arr->length);
    assert(item != NULL);

    if (index == arr->length)
    {
        da_append(arr, item, load_fun);
    }
    else
    {
        unload_fun(arr->items[index]);
        load_fun(item, &arr->items[index]);
    }
}

void da_resize(da_t *arr, size_t new_size, void (*unload_fun)(void *))
{
    assert(arr != NULL);
    assert(new_size);

    if (new_size < arr->capacity)
    {
        for (size_t i = new_size; i < arr->capacity; i++)
        {
            unload_fun(arr->items[i]);
        }
    }

    arr->items = realloc(arr->items, new_size * sizeof(void *));
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

void da_print(const da_t *arr, void (*print_func)(const void *))
{
    assert(arr != NULL);

    printf("[");

    for (size_t i = 0; i < arr->length; i++)
    {
        print_func(arr->items[i]);
        if (i < arr->length - 1)
        {
            printf(", ");
        }
    }

    printf("]\n");
}