#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cdll.h"

static cdll_node_t *cdll_create_node(const void *item, void (*load_fun)(const void *, void **))
{
    assert(item != NULL);

    cdll_node_t *new = malloc(sizeof(cdll_node_t));
    load_fun(item, &new->item);
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void cdll_create(cdll_t **list)
{
    assert(*list == NULL);

    *list = malloc(sizeof(cdll_t));
    (**list).head = NULL;
    (**list).length = 0;
}

void cdll_destroy(cdll_t **list)
{
    assert(*list != NULL);

    free(*list);
    *list = NULL;
}

void cdll_clear(cdll_t *list, void (*unload_fun)(void *))
{
    assert(list != NULL);
    assert(list->head != NULL);

    cdll_node_t *ptr = list->head;
    cdll_node_t *next;

    for (size_t i = 0; i < list->length; i++)
    {
        next = ptr->next;
        unload_fun(ptr->item);
        free(ptr);
        ptr = next;
    }
    list->head = NULL;
    list->length = 0;
}

void cdll_delete_at(cdll_t *list, size_t index, void (*unload_fun)(void *))
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(index < list->length);

    cdll_node_t *head = list->head;
    cdll_node_t *tail = head->prev;
    cdll_node_t *ptr;
    cdll_node_t *next;
    cdll_node_t *prev;

    if (!index)
    {
        ptr = head;
        next = ptr->next;
        next->prev = tail;
        tail->next = next;
        list->head = next;
    }
    else if (index == list->length - 1)
    {
        ptr = tail;
        prev = tail->prev;
        prev->next = head;
        head->prev = prev;
    }
    else
    {
        ptr = cdll_get_node_at(list, index);
        prev = ptr->prev;
        next = ptr->next;
        prev->next = next;
        next->prev = prev;
    }

    unload_fun(ptr->item);
    free(ptr);

    list->length--;
}

size_t cdll_get_index(const cdll_t *list, const void *item, int (*cmp_fun)(const void *, const void *))
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(item != NULL);

    cdll_node_t *ptr = list->head;

    int find = 0;
    size_t index = 0;
    size_t i = 0;
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

void cdll_append_front(cdll_t *list, const void *item, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);

    cdll_node_t *head = list->head;
    cdll_node_t *tail;
    cdll_node_t *new = cdll_create_node(item, load_fun);

    if (head == NULL)
    {
        new->prev = new;
        new->next = new;
    }
    else
    {
        tail = head->prev;
        tail->next = new;
        new->prev = tail;
        new->next = head;
        head->prev = new;
    }
    list->head = new;
    list->length++;
}

void cdll_append_back(cdll_t *list, const void *item, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);

    cdll_node_t *head = list->head;
    cdll_node_t *tail;
    cdll_node_t *new = cdll_create_node(item, load_fun);

    if (head == NULL)
    {
        new->prev = new;
        new->next = new;
        list->head = new;
    }
    else
    {
        tail = head->prev;
        tail->next = new;
        new->prev = tail;
        new->next = head;
        head->prev = new;
    }
    list->length++;
}

void cdll_insert_at(cdll_t *list, const void *item, size_t index, void (*load_fun)(const void *, void **))
{
    assert(list != NULL);
    assert(index <= list->length);

    cdll_node_t *head = list->head;
    cdll_node_t *ptr;
    cdll_node_t *prev;
    cdll_node_t *tail;
    cdll_node_t *new = cdll_create_node(item, load_fun);

    if (head == NULL)
    {
        new->prev = new;
        new->next = new;
        list->head = new;
    }
    else if (!index)
    {
        tail = head->prev;
        tail->next = new;
        new->prev = tail;
        new->next = head;
        head->prev = new;
        list->head = new;
    }
    else if (index == list->length)
    {
        tail = head->prev;
        tail->next = new;
        new->prev = tail;
        new->next = head;
        head->prev = new;
    }
    else
    {
        ptr = cdll_get_node_at(list, index);
        prev = ptr->prev;
        prev->next = new;
        new->prev = prev;
        new->next = ptr;
    }
    list->length++;
}

void cdll_insert_array_at(cdll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, void *arr_items[])
{
    assert(list != NULL);
    assert(index <= list->length);
    assert(arr_items != NULL);
    assert(count);

    cdll_node_t *ptr = list->head;
    cdll_node_t *ptail;
    cdll_node_t *prev;
    cdll_node_t *new;

    cdll_node_t *tail;
    cdll_node_t *head;

    void *item = arr_items[0];
    new = cdll_create_node(item, load_fun);
    prev = new;
    head = new;
    for (size_t i = 1; i < count; i++)
    {
        item = arr_items[i];
        new = cdll_create_node(item, load_fun);
        prev->next = new;
        new->prev = prev;
        prev = new;
    }
    tail = new;

    if (ptr == NULL)
    {
        head->prev = tail;
        tail->next = head;
        list->head = head;
    }
    else if (!index)
    {
        ptail = ptr->prev;
        ptail->next = head;
        head->prev = ptail;
        tail->next = ptr;
        ptr->prev = tail;
        list->head = head;
    }
    else if (index == list->length)
    {
        ptail = ptr->prev;
        ptail->next = head;
        head->prev = ptail;
        tail->next = ptr;
        ptr->prev = tail;
    }
    else
    {
        ptr = cdll_get_node_at(list, index);
        prev = ptr->prev;
        prev->next = head;
        head->prev = prev;
        tail->next = ptr;
    }

    list->length += count;
}

void cdll_insert_block_at(cdll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, ...)
{
    assert(list != NULL);
    assert(index <= list->length);
    assert(count);

    va_list ap;
    va_start(ap, count);

    cdll_node_t *ptr = list->head;
    cdll_node_t *ptail;
    cdll_node_t *prev;
    cdll_node_t *new;

    cdll_node_t *tail;
    cdll_node_t *head;

    void *item = va_arg(ap, void *);
    new = cdll_create_node(item, load_fun);
    prev = new;
    head = new;
    for (size_t i = 1; i < count; i++)
    {
        item = va_arg(ap, void *);
        new = cdll_create_node(item, load_fun);
        prev->next = new;
        new->prev = prev;
        prev = new;
    }
    tail = new;

    if (ptr == NULL)
    {
        head->prev = tail;
        tail->next = head;
        list->head = head;
    }
    else if (!index)
    {
        ptail = ptr->prev;
        ptail->next = head;
        head->prev = ptail;
        tail->next = ptr;
        ptr->prev = tail;
        list->head = head;
    }
    else if (index == list->length)
    {
        ptail = ptr->prev;
        ptail->next = head;
        head->prev = ptail;
        tail->next = ptr;
        ptr->prev = tail;
    }
    else
    {
        ptr = cdll_get_node_at(list, index);
        prev = ptr->prev;
        prev->next = head;
        head->prev = prev;
        tail->next = ptr;
    }

    list->length += count;
    va_end(ap);
}

cdll_node_t *cdll_get_node_at(const cdll_t *list, size_t index)
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(index <= list->length);

    cdll_node_t *phead = list->head;
    cdll_node_t *ptail = phead->prev;

    if (index <= list->length / 2)
    {
        while (index--)
        {
            phead = phead->next;
        }
        return phead;
    }
    else
    {
        index = list->length - index - 1;
        while (index--)
        {
            ptail = ptail->prev;
        }
        return ptail;
    }
}

void *cdll_get_at(const cdll_t *list, size_t index)
{
    assert(list != NULL);
    assert(list->head != NULL);
    assert(index < list->length);

    cdll_node_t *ptr = cdll_get_node_at(list, index);
    return ptr->item;
}

void cdll_set_at(cdll_t *list, size_t index, const void *item, void (*unload_fun)(void *), void (*load_fun)(const void *, void **))
{
    assert(list != NULL);
    assert(index <= list->length);

    cdll_node_t *ptr = list->head;
    cdll_node_t *tail;
    cdll_node_t *prev;
    cdll_node_t *next;
    cdll_node_t *new = cdll_create_node(item, load_fun);

    if (ptr == NULL)
    {
        new->prev = new;
        new->next = new;
        list->head = new;
        list->length++;
    }
    else if (index == list->length)
    {
        tail = ptr->prev;
        tail->next = new;
        new->prev = tail;
        new->next = ptr;
        ptr->prev = new;
        list->length++;
    }
    else
    {
        tail = ptr->prev;
        if (!index)
        {
            next = ptr->next;
            tail->next = new;
            new->prev = tail;
            new->next = next;
            next->prev = new;
            list->head = new;
        }
        else if (index == list->length - 1)
        {
            ptr = tail;
            prev = tail->prev;
            prev->next = new;
            new->prev = prev;
            new->next = list->head;
        }
        else
        {
            ptr = cdll_get_node_at(list, index);
            next = ptr->next;
            prev = ptr->prev;
            prev->next = new;
            new->prev = prev;
            new->next = next;
            next->prev = new;
        }
        unload_fun(ptr->item);
        free(ptr);
    }
}

size_t cdll_size(const cdll_t *list)
{
    assert(list != NULL);

    return list->length;
}

void cdll_print(const cdll_t *list, void (*print_func)(const void *))
{
    assert(list != NULL);

    cdll_node_t *ptr = list->head;

    printf("[");

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