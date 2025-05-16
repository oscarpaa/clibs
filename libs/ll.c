#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ll.h"

static ll_node_t *ll_create_node(const void *item, void (*load_fun)(const void *, void **))
{
    assert(item != NULL);

    ll_node_t *new = malloc(sizeof(ll_node_t));
    load_fun(item, &new->item);
    new->next = NULL;
    return new;
}

void ll_create(ll_t **list)
{
    assert(*list == NULL);

    *list = malloc(sizeof(ll_t));
    (**list).head = NULL;
    (**list).length = 0;
}

void ll_destroy(ll_t **list)
{
    assert(*list != NULL);
    assert(!(**list).length);

    free(*list);
    *list = NULL;
}

void ll_clear(ll_t *list, void (*unload_fun)(void *))
{
    assert(list != NULL);
    assert(list->head != NULL);

    ll_node_t *ptr = list->head;
    ll_node_t *next;

    while (ptr->next != NULL)
    {
        next = ptr->next;
        unload_fun(ptr->item);
        free(ptr);
        ptr = next;
    }
    list->head = NULL;
    list->length = 0;
}

void ll_delete_at(ll_t *list, size_t index, void (*unload_fun)(void *))
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(index < list->length);

    ll_node_t *ptr = list->head;
    ll_node_t *prev;

    if (!index)
    {
        list->head = ptr->next;
    }
    else
    {
        ptr = ll_get_node_at(list, index, &prev);
        prev->next = ptr->next;
    }
    unload_fun(ptr->item);
    free(ptr);

    list->length--;
}

size_t ll_get_index(const ll_t *list, const void *item, int (*cmp_fun)(const void *, const void *))
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(item != NULL);

    int find = 0;
    size_t index = 0;
    ll_node_t *ptr = list->head;
    while (ptr != NULL && !find)
    {
        if (!cmp_fun(item, ptr->item))
        {
            find = 1;
        }
        else
        {
            index++;
        }
        ptr = ptr->next;
    }
    return index;
}

void ll_append_front(ll_t *list, const void *item, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);

    ll_node_t *ptr = list->head;
    ll_node_t *new = ll_create_node(item, load_fun);

    if (ptr != NULL)
    {
        new->next = ptr;
    }
    list->head = new;
    list->length++;
}

void ll_append_back(ll_t *list, const void *item, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);

    ll_node_t *ptr = list->head;
    ll_node_t *new = ll_create_node(item, load_fun);
    if (ptr == NULL)
    {
        list->head = new;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new;
    }
    list->length++;
}

void ll_insert_at(ll_t *list, const void *item, size_t index, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);
    assert(index <= list->length);

    ll_node_t *ptr = list->head;
    ll_node_t *prev;
    ll_node_t *new = ll_create_node(item, load_fun);

    if (ptr == NULL)
    {
        list->head = new;
    }
    else if (!index)
    {
        list->head = new;
        new->next = ptr;
    }
    else
    {
        ptr = ll_get_node_at(list, index, &prev);
        prev->next = new;
        new->next = ptr;
    }
    list->length++;
}

void ll_insert_array_at(ll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, void *arr_items[])
{
    assert(list != NULL);
    assert(index <= list->length);
    assert(arr_items != NULL);
    assert(count);

    ll_node_t *ptr = list->head;
    ll_node_t *prev;
    ll_node_t *new;

    ll_node_t *tail;
    ll_node_t *head;

    void *item = arr_items[0];
    new = ll_create_node(item, load_fun);
    prev = new;
    head = new;
    for (size_t i = 1; i < count; i++)
    {
        item = arr_items[i];
        new = ll_create_node(item, load_fun);
        prev->next = new;
        prev = new;
    }
    tail = new;

    if (ptr == NULL)
    {
        list->head = head;
    }
    else if (!index)
    {
        list->head = head;
        tail->next = ptr;
    }
    else
    {
        ptr = ll_get_node_at(list, index, &prev);
        prev->next = head;
        tail->next = ptr;
    }

    list->length += count;
}

void ll_insert_block_at(ll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, ...)
{
    assert(list != NULL);
    assert(index <= list->length);
    assert(count);

    va_list ap;
    va_start(ap, count);

    ll_node_t *ptr = list->head;
    ll_node_t *prev;
    ll_node_t *new;

    ll_node_t *tail;
    ll_node_t *head;

    void *item = va_arg(ap, void *);
    new = ll_create_node(item, load_fun);
    prev = new;
    head = new;
    for (size_t i = 1; i < count; i++)
    {
        item = va_arg(ap, void *);
        new = ll_create_node(item, load_fun);
        prev->next = new;
        prev = new;
    }
    tail = new;

    if (ptr == NULL)
    {
        list->head = head;
    }
    else if (!index)
    {
        list->head = head;
        tail->next = ptr;
    }
    else
    {
        ptr = ll_get_node_at(list, index, &prev);
        prev->next = head;
        tail->next = ptr;
    }

    list->length += count;
    va_end(ap);
}

ll_node_t *ll_get_node_at(const ll_t *list, size_t index, ll_node_t **prev)
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(index <= list->length);

    ll_node_t *ptr = list->head;

    while (index--)
    {
        if (prev != NULL)
        {
            *prev = ptr;
        }
        ptr = ptr->next;
    }
    return ptr;
}

void *ll_get_at(const ll_t *list, size_t index)
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(index < list->length);

    ll_node_t *ptr = ll_get_node_at(list, index, NULL);
    return ptr->item;
}

void ll_set_at(ll_t *list, size_t index, const void *item, void (*unload_fun)(void *), void (*load_fun)(const void *, void **))
{
    assert(list != NULL);
    assert(index <= list->length);

    ll_node_t *ptr = list->head;
    ll_node_t *prev;
    ll_node_t *new = ll_create_node(item, load_fun);

    if (ptr == NULL)
    {
        list->head = new;
        list->length++;
    }
    else if (index == list->length)
    {
        ptr = ll_get_node_at(list, index, &prev);
        prev->next = new;
        new->next = ptr;
        list->length++;
    }
    else
    {
        if (!index)
        {
            list->head = new;
            new->next = ptr->next;
        }
        else
        {
            ptr = ll_get_node_at(list, index, &prev);
            prev->next = new;
            new->next = ptr->next;
        }
        unload_fun(ptr->item);
        free(ptr);
    }
}

size_t ll_size(const ll_t *list)
{
    assert(list != NULL);

    return list->length;
}

void ll_print(const ll_t *list, void (*print_func)(const void *))
{
    assert(list != NULL);

    ll_node_t *ptr = list->head;

    printf("[");

    while (ptr != NULL)
    {
        print_func(ptr->item);
        if (ptr->next != NULL)
        {
            printf(", ");
        }
        ptr = ptr->next;
    }

    printf("]\n");
}