#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cll.h"

static cll_node_t *cll_create_node(const void *item, void (*load_fun)(const void *, void **))
{
    assert(item != NULL);

    cll_node_t *new = malloc(sizeof(cll_node_t));
    load_fun(item, &new->item);
    new->next = NULL;
    return new;
}

void cll_create(cll_t **list)
{
    assert(*list == NULL);

    *list = malloc(sizeof(cll_t));
    (**list).tail = NULL;
    (**list).length = 0;
}

void cll_destroy(cll_t **list)
{
    assert(*list != NULL);

    free(*list);
    *list = NULL;
}

void cll_clear(cll_t *list, void (*unload_fun)(void *))
{
    assert(list != NULL);
    assert(list->tail != NULL);

    cll_node_t *ptr = list->tail;
    cll_node_t *next;

    for (size_t i = 0; i < list->length; i++)
    {
        next = ptr->next;
        unload_fun(ptr->item);
        free(ptr);
        ptr = next;
    }
    list->tail = NULL;
    list->length = 0;
}

void cll_delete_at(cll_t *list, size_t index, void (*unload_fun)(void *))
{
    assert(list != NULL);
    assert(list->tail != NULL);
    assert(index < list->length);

    cll_node_t *ptr = list->tail;
    cll_node_t *head = ptr->next;
    cll_node_t *prev;

    size_t i = index;

    if (!index)
    {
        ptr->next = head->next;
        ptr = head;
    }
    else
    {
        ptr = cll_get_node_at(list, index, &prev);
        prev->next = ptr->next;
        if (i == list->length - 1)
        {
            list->tail = prev;
        }
    }
    unload_fun(ptr->item);
    free(ptr);

    list->length--;
}

size_t cll_get_index(const cll_t *list, const void *item, int (*cmp_fun)(const void *, const void *))
{
    assert(list != NULL);
    assert(list->tail != NULL);
    assert(item != NULL);

    cll_node_t *ptr = list->tail;

    int find = 0;
    size_t index = 0;
    size_t i = 0;

    if (!cmp_fun(item, ptr->item))
    {
        find = 1;
        index = list->length - 1;
    }
    ptr = ptr->next;
    while (i < list->length - 1 && !find)
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
        i++;
    }
    return index;
}

void cll_append_front(cll_t *list, const void *item, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);

    cll_node_t *ptr = list->tail;
    cll_node_t *head;
    cll_node_t *new = cll_create_node(item, load_fun);

    if (ptr == NULL)
    {
        new->next = new;
        list->tail = new;
    }
    else
    {
        head = ptr->next;
        new->next = head;
        ptr->next = new;
    }
    list->length++;
}

void cll_append_back(cll_t *list, const void *item, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);

    cll_node_t *ptr = list->tail;
    cll_node_t *head;
    cll_node_t *new = cll_create_node(item, load_fun);
    if (ptr == NULL)
    {
        new->next = new;
    }
    else
    {
        head = ptr->next;
        ptr->next = new;
        new->next = head;
    }
    list->tail = new;
    list->length++;
}

void cll_insert_at(cll_t *list, const void *item, size_t index, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);
    assert(index <= list->length);

    cll_node_t *ptr = list->tail;
    cll_node_t *head;
    cll_node_t *prev;
    cll_node_t *new = cll_create_node(item, load_fun);

    if (ptr == NULL)
    {
        new->next = new;
        list->tail = new;
    }
    else if (!index)
    {
        head = ptr->next;
        new->next = head;
        ptr->next = new;
    }
    else if (index == list->length)
    {
        head = ptr->next;
        new->next = head;
        ptr->next = new;
        list->tail = new;
    }
    else
    {
        ptr = cll_get_node_at(list, index, &prev);
        prev->next = new;
        new->next = ptr;
    }
    list->length++;
}

void cll_insert_array_at(cll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, void *arr_items[])
{
    assert(list != NULL);
    assert(index <= list->length);
    assert(arr_items != NULL);
    assert(count);

    cll_node_t *ptr = list->tail;
    cll_node_t *prev;
    cll_node_t *new;

    cll_node_t *tail;
    cll_node_t *head;

    void *item = arr_items[0];
    new = cll_create_node(item, load_fun);
    prev = new;
    head = new;
    for (size_t i = 1; i < count; i++)
    {
        item = arr_items[i];
        new = cll_create_node(item, load_fun);
        prev->next = new;
        prev = new;
    }
    tail = new;

    if (ptr == NULL)
    {
        list->tail = tail;
        tail->next = head;
    }
    else if (!index)
    {
        tail->next = ptr->next;
        ptr->next = head;
    }
    else if (index == list->length)
    {
        tail->next = ptr->next;
        ptr->next = head;
        list->tail = tail;
    }
    else
    {
        ptr = cll_get_node_at(list, index, &prev);
        prev->next = head;
        tail->next = ptr;
    }

    list->length += count;
}

void cll_insert_block_at(cll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, ...)
{
    assert(list != NULL);
    assert(index <= list->length);
    assert(count);

    va_list ap;
    va_start(ap, count);

    cll_node_t *ptr = list->tail;
    cll_node_t *prev;
    cll_node_t *new;

    cll_node_t *tail;
    cll_node_t *head;

    void *item = va_arg(ap, void *);
    new = cll_create_node(item, load_fun);
    prev = new;
    head = new;
    for (size_t i = 1; i < count; i++)
    {
        item = va_arg(ap, void *);
        new = cll_create_node(item, load_fun);
        prev->next = new;
        prev = new;
    }
    tail = new;

    if (ptr == NULL)
    {
        list->tail = tail;
        tail->next = head;
    }
    else if (!index)
    {
        tail->next = ptr->next;
        ptr->next = head;
    }
    else if (index == list->length)
    {
        tail->next = ptr->next;
        ptr->next = head;
        list->tail = tail;
    }
    else
    {
        ptr = cll_get_node_at(list, index, &prev);
        prev->next = head;
        tail->next = ptr;
    }

    list->length += count;
    va_end(ap);
}

cll_node_t *cll_get_node_at(const cll_t *list, size_t index, cll_node_t **prev)
{
    assert(list != NULL);
    assert(list->tail != NULL);
    assert(index <= list->length);

    cll_node_t *ptr = list->tail;

    if (index == list->length - 1 && prev == NULL)
    {
        return ptr;
    }

    ptr = ptr->next;
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

void *cll_get_at(const cll_t *list, size_t index)
{
    assert(list != NULL);
    assert(list->tail != NULL);
    assert(index < list->length);

    cll_node_t *ptr = cll_get_node_at(list, index, NULL);
    return ptr->item;
}

void cll_set_at(cll_t *list, size_t index, const void *item, void (*unload_fun)(void *), void (*load_fun)(const void *, void **))
{
    assert(list != NULL);
    assert(index <= list->length);

    cll_node_t *ptr = list->tail;
    cll_node_t *head;
    cll_node_t *prev;
    cll_node_t *new = cll_create_node(item, load_fun);

    if (ptr == NULL)
    {
        list->tail = new;
        new->next = new;
        list->length++;
    }
    else if (index == list->length)
    {
        head = ptr->next;
        new->next = head;
        ptr->next = new;
        list->tail = new;
        list->length++;
    }
    else
    {
        if (!index)
        {
            head = ptr->next;
            ptr->next = new;
            new->next = head->next;
            ptr = head;
        }
        else
        {
            if (index == list->length - 1)
            {
                list->tail = new;
            }
            ptr = cll_get_node_at(list, index, &prev);
            prev->next = new;
            new->next = ptr->next;
        }
        unload_fun(ptr->item);
        free(ptr);
    }
}

size_t cll_size(const cll_t *list)
{
    assert(list != NULL);

    return list->length;
}

void cll_print(const cll_t *list, void (*print_func)(const void *))
{
    assert(list != NULL);

    cll_node_t *ptr = list->tail;

    printf("[");

    if (list->length > 1)
    {
        ptr = ptr->next;
    }
    for (size_t i = 0; i < list->length; i++)
    {
        print_func(ptr->item);
        if (i < list->length - 1)
        {
            printf(", ");
        }
        ptr = ptr->next;
    }

    printf("]\n");
}