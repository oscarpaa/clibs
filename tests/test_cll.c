#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "cll.h"

typedef struct _token_t
{
    char *name;
    size_t index;
    size_t type;
} token_t;

void print_tok(const void *item)
{
    printf("{%s, ", ((token_t *)item)->name);
    printf("%d, ", ((token_t *)item)->index);
    printf("%d}", ((token_t *)item)->type);
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

void unload_tok(void *item)
{
    free(((token_t *)item)->name);
    free(item);
}

// TESTS

void test1(cll_t **list1)
{
    printf("====== TEST 1 ======\n");

    cll_append_front(*list1, &(int){67}, load_int);
    cll_print(*list1, print_int);

    cll_append_back(*list1, &(int){1}, load_int);
    cll_print(*list1, print_int);

    cll_append_back(*list1, &(int){2}, load_int);
    cll_print(*list1, print_int);

    cll_append_back(*list1, &(int){3}, load_int);
    cll_print(*list1, print_int);

    cll_append_front(*list1, &(int){99}, load_int);
    cll_print(*list1, print_int);

    cll_append_back(*list1, &(int){12}, load_int);
    cll_print(*list1, print_int);

    int *c;
    c = cll_get_at(*list1, 3);
    printf("Index: %d\n", *c);

    printf("Items: %d\n", cll_size(*list1));

    printf("Index: %d\n", cll_get_index(*list1, &(int){12}, compare_int));

    cll_replace_at(*list1, 1, &(int){555}, unload, load_int);
    cll_print(*list1, print_int);
}

void test2(cll_t **list2)
{
    printf("====== TEST 2 ======\n");

    cll_append_back(*list2, "hola", load_ch);
    cll_append_back(*list2, "mundo", load_ch);

    char *m[10] = {"This", "is", "a", "test"};

    cll_insert_array_at(*list2, 1, load_ch, 4, (void **)m);
    cll_print(*list2, print_ch);

    cll_append_front(*list2, "ahhhhh", load_ch);
    cll_insert_at(*list2, "!!!!", 0, load_ch);

    cll_print(*list2, print_ch);

    cll_delete_at(*list2, 0, unload);
    cll_print(*list2, print_ch);

    cll_replace_at(*list2, 2, "KEWW", unload, load_ch);
    cll_print(*list2, print_ch);

    cll_insert_block_at(*list2, 2, load_ch, 3, "esto", "es", "dificil");
    cll_print(*list2, print_ch);

    printf("Index: %d\n", cll_get_index(*list2, "KEWW", compare_ch));
}

void test3(cll_t **list3)
{
    printf("====== TEST 3 ======\n");

    cll_append_back(*list3, &(token_t){"HOLA", 1, 2}, load_tok);
    cll_append_back(*list3, &(token_t){"mundo", 4, 2}, load_tok);

    cll_print(*list3, print_tok);
}

int main(int argc, char const *argv[])
{
    cll_t *list1 = NULL;
    cll_t *list2 = NULL;
    cll_t *list3 = NULL;

    cll_create(&list1);
    cll_create(&list2);
    cll_create(&list3);

    test1(&list1);
    test2(&list2);
    test3(&list3);

    cll_clear(list1, unload);
    cll_clear(list2, unload);
    cll_clear(list3, unload_tok);

    cll_destroy(&list1);
    cll_destroy(&list2);
    cll_destroy(&list3);

    return 0;
}
