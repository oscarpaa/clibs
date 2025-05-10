#ifndef __CIRCULAR_S_LL__
#define __CIRCULAR_S_LL__

typedef struct _cll_node_t
{
    void *item;
    struct _cll_node_t *next;
} cll_node_t;

typedef struct _cll_t
{
    cll_node_t *tail;
    size_t length;
} cll_t;

void cll_create(cll_t **list);
void cll_destroy(cll_t **list);
void cll_clear(cll_t *list, void (*unload_fun)(void *));
void cll_delete_at(cll_t *list, size_t index, void (*unload_fun)(void *));
size_t cll_get_index(const cll_t *list, const void *item, int (*cmp_fun)(const void *, const void *));
void cll_append_front(cll_t *list, const void *item, void (*load_fun)(const void *, void **));
void cll_append_back(cll_t *list, const void *item, void (*load_fun)(const void *, void **));
void cll_insert_at(cll_t *list, const void *item, size_t index, void (*load_fun)(const void *, void **));
void cll_insert_array_at(cll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, void *arr_items[]);
void cll_insert_block_at(cll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, ...);
cll_node_t *cll_get_node_at(const cll_t *list, size_t index, cll_node_t **prev);
void *cll_get_at(const cll_t *list, size_t index);
void cll_set_at(cll_t *list, size_t index, const void *item, void (*unload_fun)(void *), void (*load_fun)(const void *, void **));
size_t cll_size(const cll_t *list);
void cll_print(const cll_t *list, void (*print_func)(const void *));

#endif /* __CIRCULAR_S_LL__ */