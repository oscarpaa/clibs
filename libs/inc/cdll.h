#ifndef __CIRCULAR_D_LL__
#define __CIRCULAR_D_LL__

typedef struct _cdll_node_t
{
    void *item;
    struct _cdll_node_t *prev;
    struct _cdll_node_t *next;
} cdll_node_t;

typedef struct _cdll_t
{
    cdll_node_t *head;
    size_t length;
} cdll_t;

void cdll_create(cdll_t **list);
void cdll_destroy(cdll_t **list);
void cdll_clear(cdll_t *list, void (*unload_fun)(void *));
void cdll_delete_at(cdll_t *list, size_t index, void (*unload_fun)(void *));
size_t cdll_get_index(const cdll_t *list, const void *item, int (*cmp_fun)(const void *, const void *));
void cdll_append_front(cdll_t *list, const void *item, void (*load_fun)(const void *, void **));
void cdll_append_back(cdll_t *list, const void *item, void (*load_fun)(const void *, void **));
void cdll_insert_at(cdll_t *list, const void *item, size_t index, void (*load_fun)(const void *, void **));
void cdll_insert_array_at(cdll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, void *arr_items[]);
void cdll_insert_block_at(cdll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, ...);
cdll_node_t *cdll_get_node_at(const cdll_t *list, size_t index);
void *cdll_get_at(const cdll_t *list, size_t index);
void cdll_set_at(cdll_t *list, size_t index, const void *item, void (*unload_fun)(void *), void (*load_fun)(const void *, void **));
size_t cdll_size(const cdll_t *list);
void cdll_print(const cdll_t *list, void (*print_func)(const void *));

#endif /* __CIRCULAR_D_LL__ */