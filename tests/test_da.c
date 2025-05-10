#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "da.h"

int main(int argc, char const *argv[])
{
    da_t *arr1 = NULL;

    da_create(&arr1);

    da_append_back(arr1, &(char){'h'}, sizeof(char));
    da_append_back(arr1, &(char){'o'}, sizeof(char));
    da_append_back(arr1, &(char){'l'}, sizeof(char));
    da_append_back(arr1, &(char){'a'}, sizeof(char));
    da_append_back(arr1, &(char){'!'}, sizeof(char));

    da_print(arr1, sizeof(char), print_c);

    da_resize(arr1, 3, sizeof(char));

    da_print(arr1, sizeof(char), print_c);

    da_destroy(&arr1);

    da_t *arr2 = NULL;
    da_create(&arr2);

    da_append_back(arr2, &(int){12}, sizeof(int));
    da_append_back(arr2, &(int){2}, sizeof(int));
    da_append_back(arr2, &(int){67}, sizeof(int));

    da_print(arr2, sizeof(int), print_int);

    da_destroy(&arr2);


    return 0;
}
