#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

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
    return *(int *)item1 == *(int *)item2 ? 0 : 1;
}

int compare_ch(const void *item1, const void *item2)
{
    return strcmp(item1, item2);
}

// TESTS

void test1(ll_t **list1)
{
    printf("====== TEST 1 ======\n");

    ll_append_front(*list1, &(int){67}, load_int);
    ll_print(*list1, print_int);

    ll_append_back(*list1, &(int){1}, load_int);
    ll_print(*list1, print_int);

    ll_append_back(*list1, &(int){2}, load_int);
    ll_print(*list1, print_int);

    ll_append_back(*list1, &(int){3}, load_int);
    ll_print(*list1, print_int);

    ll_append_front(*list1, &(int){99}, load_int);
    ll_print(*list1, print_int);

    ll_append_back(*list1, &(int){12}, load_int);
    ll_print(*list1, print_int);

    int *c;
    c = ll_get_at(*list1, 3);
    printf("Index: %d\n", *c);

    printf("Items: %d\n", ll_size(*list1));

    printf("Index: %d\n", ll_get_index(*list1, &(int){12}, compare_int));

    ll_replace_at(*list1, 1, &(int){555}, unload, load_int);
    ll_print(*list1, print_int);
}

void test2(ll_t **list2)
{
    printf("====== TEST 2 ======\n");

    ll_append_back(*list2, "hola", load_ch);
    ll_append_back(*list2, "mundo", load_ch);
    ll_append_front(*list2, "ahhhhh", load_ch);
    ll_insert_at(*list2, "!!!!", 0, load_ch);

    ll_print(*list2, print_ch);

    ll_delete_at(*list2, 0, unload);
    ll_print(*list2, print_ch);

    ll_replace_at(*list2, 0, "KEWW", unload, load_ch);
    ll_print(*list2, print_ch);

    ll_insert_block_at(*list2, 2, load_ch, 3, "esto", "es", "dificil");
    ll_print(*list2, print_ch);

    printf("Index: %d\n", ll_get_index(*list2, "KEWW", compare_ch));
}

void test3(ll_t **list3)
{
    printf("====== TEST 3 ======\n");

    ll_append_back(*list3, &(token_t){"HOLA", 1, 2}, load_tok);
    ll_append_back(*list3, &(token_t){"mundo", 4, 2}, load_tok);

    ll_print(*list3, print_tok);
}

int main(int argc, char const *argv[])
{
    ll_t *list1 = NULL;
    ll_t *list2 = NULL;
    ll_t *list3 = NULL;

    ll_create(&list1);
    ll_create(&list2);
    ll_create(&list3);

    test1(&list1);
    test2(&list2);
    test3(&list3);

    printf("\n=====================\n");

    ll_print(list1, print_int);
    ll_print(list2, print_ch);
    ll_print(list3, print_tok);

    printf("=====================\n");

    ll_clear(list1, unload);
    ll_clear(list2, unload);
    ll_clear(list3, unload_tok);

    ll_destroy(&list1);
    ll_destroy(&list2);
    ll_destroy(&list3);

    return 0;
}
