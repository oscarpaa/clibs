#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "da.h"

static void da_reserve(da_t *arr, size_t expected)
{
    assert(arr != NULL);
    assert(expected);

    if (expected > arr->capacity)
    {
        while (expected > arr->capacity)
        {
            arr->capacity *= 2;
        }
        arr->items = realloc(arr->items, arr->capacity * sizeof(void *));
    }
}

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

void da_delete_at(da_t *arr, size_t index, void (*unload_fun)(void *))
{
    assert(arr != NULL);
    assert(index < arr->length);

    unload_fun(arr->items[index]);
    arr->length--;

    for (size_t i = index; i < arr->length; i++)
    {
        arr->items[i] = arr->items[i + 1];
    }
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

    da_reserve(arr, arr->length + 1);

    load_fun(item, &arr->items[arr->length]);
    arr->length++;
}

void da_append_array(da_t *arr, void (*load_fun)(const void *, void **), size_t count, void *arr_items[])
{
    assert(arr != NULL);
    assert(arr_items != NULL);
    assert(count);

    da_reserve(arr, arr->length + count + 1);

    for (size_t i = 0; i < count; i++)
    {
        load_fun(arr_items[i], &arr->items[i + arr->length]);
    }
    arr->length += count;
}

void da_append_block(da_t *arr, void (*load_fun)(const void *, void **), size_t count, ...)
{
    assert(arr != NULL);
    assert(count);

    va_list ap;
    va_start(ap, count);

    da_reserve(arr, arr->length + count + 1);

    void *item;
    for (size_t i = 0; i < count; i++)
    {
        item = va_arg(ap, void *);
        load_fun(item, &arr->items[i + arr->length]);
    }
    arr->length += count;

    va_end(ap);
}

void da_insert_at(da_t *arr, const void *item, size_t index, void (*load_fun)(const void *, void **))
{
    assert(arr != NULL);
    assert(item != NULL);
    assert(index <= arr->length);

    da_reserve(arr, arr->length + 1);

    for (size_t i = arr->length; i > index; i--)
    {
        arr->items[i] = arr->items[i - 1];
    }

    load_fun(item, &arr->items[index]);
    arr->length++;
}

void da_insert_array_at(da_t *arr, size_t index, void (*load_fun)(const void *, void **), size_t count, void *arr_items[])
{
    assert(arr != NULL);
    assert(index <= arr->length);
    assert(arr_items != NULL);
    assert(count);

    da_reserve(arr, arr->length + count + 1);

    for (size_t i = arr->length + count - 1; i > index + count - 1; i--)
    {
        arr->items[i] = arr->items[i - count];
    }

    for (size_t i = 0; i < count; i++)
    {
        load_fun(arr_items[i], &arr->items[i + index]);
    }
    arr->length += count;
}

void da_insert_block_at(da_t *arr, size_t index, void (*load_fun)(const void *, void **), size_t count, ...)
{
    assert(arr != NULL);
    assert(index <= arr->length);
    assert(count);

    va_list ap;
    va_start(ap, count);

    void *item;

    da_reserve(arr, arr->length + count + 1);

    for (size_t i = arr->length + count - 1; i > index + count - 1; i--)
    {
        arr->items[i] = arr->items[i - count];
    }

    for (size_t i = 0; i < count; i++)
    {
        item = va_arg(ap, void *);
        load_fun(item, &arr->items[i + index]);
    }
    arr->length += count;

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