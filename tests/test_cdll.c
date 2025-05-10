#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "cdll.h"

void test1(cdll_t **list1)
{
    printf("====== TEST 1 ======\n");

    cdll_append_front(*list1, &(int){67}, load_int);
    cdll_print(*list1, print_int);

    cdll_insert_at(*list1, &(int){129}, 1, load_int);
    cdll_print(*list1, print_int);

    cdll_append_back(*list1, &(int){1}, load_int);
    cdll_print(*list1, print_int);

    cdll_append_back(*list1, &(int){2}, load_int);
    cdll_print(*list1, print_int);

    cdll_append_back(*list1, &(int){3}, load_int);
    cdll_print(*list1, print_int);

    cdll_append_front(*list1, &(int){99}, load_int);
    cdll_print(*list1, print_int);

    cdll_append_back(*list1, &(int){12}, load_int);
    cdll_print(*list1, print_int);

    int *c;
    c = cdll_get_at(*list1, 3);
    printf("Index: %d\n", *c);

    printf("Items: %d\n", cdll_size(*list1));

    printf("Index: %d\n", cdll_get_index(*list1, &(int){12}, compare_int));

    cdll_set_at(*list1, 1, &(int){555}, unload, load_int);
    cdll_print(*list1, print_int);
}

void test2(cdll_t **list2)
{
    printf("====== TEST 2 ======\n");

    cdll_append_back(*list2, "hola", load_ch);
    cdll_append_back(*list2, "mundo", load_ch);

    char *m[10] = {"This", "is", "a", "test"};

    cdll_insert_array_at(*list2, 1, load_ch, 4, (void **)m);
    cdll_print(*list2, print_ch);

    cdll_append_front(*list2, "ahhhhh", load_ch);
    cdll_insert_at(*list2, "!!!!", 0, load_ch);

    cdll_print(*list2, print_ch);

    cdll_delete_at(*list2, 0, unload);
    cdll_print(*list2, print_ch);

    cdll_set_at(*list2, 2, "KEWW", unload, load_ch);
    cdll_print(*list2, print_ch);

    cdll_insert_block_at(*list2, 2, load_ch, 3, "esto", "es", "dificil");
    cdll_print(*list2, print_ch);

    printf("Index: %d\n", cdll_get_index(*list2, "KEWW", compare_ch));
}

void test3(cdll_t **list3)
{
    printf("====== TEST 3 ======\n");

    cdll_set_at(*list3, 0, &(token_t){"siuu", 10, 0}, unload_tok, load_tok);
    cdll_print(*list3, print_tok);

    cdll_append_back(*list3, &(token_t){"HOLA", 1, 2}, load_tok);
    cdll_append_back(*list3, &(token_t){"mundo", 4, 2}, load_tok);
    cdll_print(*list3, print_tok);

    cdll_set_at(*list3, 1, &(token_t){"meme", 10, 0}, unload_tok, load_tok);
    cdll_print(*list3, print_tok);

    cdll_set_at(*list3, 3, &(token_t){"five", 2, 7}, unload_tok, load_tok);
    cdll_print(*list3, print_tok);
}

int main(int argc, char const *argv[])
{
    cdll_t *list1 = NULL;
    cdll_t *list2 = NULL;
    cdll_t *list3 = NULL;

    cdll_create(&list1);
    cdll_create(&list2);
    cdll_create(&list3);

    test1(&list1);
    test2(&list2);
    test3(&list3);

    cdll_clear(list1, unload);
    cdll_clear(list2, unload);
    cdll_clear(list3, unload_tok);

    cdll_destroy(&list1);
    cdll_destroy(&list2);
    cdll_destroy(&list3);

    printf("\nExiting...\n");

    return 0;
}
