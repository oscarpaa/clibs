#ifndef __DINAMIC_ARRAY__
#define __DINAMIC_ARRAY__

typedef struct _da_t
{
    void **items;
    size_t length;
    size_t capacity;
} da_t;

void da_create(da_t **arr, size_t init_cap);
void da_destroy(da_t **arr);
void da_clear(da_t *arr, void (*unload_fun)(void *));
void da_delete_at(da_t *arr, size_t index, void (*unload_fun)(void *));
size_t da_get_index(const da_t *arr, const void *item, int (*cmp_fun)(const void *, const void *));
void da_append(da_t *arr, const void *item, void (*load_fun)(const void *, void **));
void da_append_array(da_t *arr, void (*load_fun)(const void *, void **), size_t count, void *arr_items[]);
void da_append_block(da_t *arr, void (*load_fun)(const void *, void **), size_t count, ...);
void da_insert_at(da_t *arr, const void *item, size_t index, void (*load_fun)(const void *, void **));
void da_insert_array_at(da_t *arr, size_t index, void (*load_fun)(const void *, void **), size_t count, void *arr_items[]);
void da_insert_block_at(da_t *arr, size_t index, void (*load_fun)(const void *, void **), size_t count, ...);
void *da_get_at(const da_t *arr, size_t index);
void da_set_at(da_t *arr, size_t index, const void *item, void (*unload_fun)(void *), void (*load_fun)(const void *, void **));
void da_resize(da_t *arr, size_t new_size, void (*unload_fun)(void *));
size_t da_size(const da_t *arr);
size_t da_capacity(const da_t *arr);
void da_print(const da_t *arr, void (*print_func)(const void *));

#endif /* __DINAMIC_ARRAY__ */