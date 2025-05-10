#ifndef __DINAMIC_ARRAY__
#define __DINAMIC_ARRAY__

#ifndef DA_INIT_CAP
#define DA_INIT_CAP 256
#endif /* DA_INIT_CAP */

typedef struct _da_t
{
    void *items;
    size_t length;
    size_t capacity;
} da_t;

void da_create(da_t **arr);
void da_destroy(da_t **arr);
void da_append_back(da_t *arr, const void *item, size_t size_item);
void da_resize(da_t *arr, size_t new_size, size_t size_item);
size_t da_size(const da_t *arr);
size_t da_capacity(const da_t *arr);
void da_print(const da_t *arr, size_t size_item, void (*print_func)(const void *));

#endif /* __DINAMIC_ARRAY__ */