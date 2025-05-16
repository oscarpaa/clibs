#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "da.h"

int main(int argc, char const *argv[])
{
    da_t *arr1 = NULL;

    da_create(&arr1, 5);

    da_append(arr1, "hola mundo", load_ch);
    da_append(arr1, "Esto es una prueba", load_ch);
    da_print(arr1, print_ch);

    da_append_block(arr1, load_ch, 2, "3aa", "2bb");
    da_delete(arr1, unload);
    da_print(arr1, print_ch);

    // da_clear(arr1, unload);
    // da_destroy(&arr1);

    da_t *arr2 = NULL;
    da_create(&arr2, 2);

    da_append(arr2, &(int){12}, load_int);
    da_append(arr2, &(int){2}, load_int);
    da_append(arr2, &(int){67}, load_int);

    da_print(arr2, print_int);

    da_set_at(arr2, 1, &(int){666}, unload, load_int);

    da_delete(arr2, unload);
    da_delete(arr2, unload);
    da_delete(arr2, unload);
    da_append(arr2, &(int){89}, load_int);
    da_print(arr2, print_int);

    da_clear(arr2, unload);
    da_destroy(&arr2);

    da_t *arr3 = NULL;
    da_create(&arr3, 5);

    da_append_array(arr3, load_ch, arr1->length, arr1->items);
    da_append(arr3, "como?", load_ch);
    da_print(arr3, print_ch);

    da_clear(arr3, unload);
    da_destroy(&arr3);

    printf("\nExiting...\n");

    return 0;
}
