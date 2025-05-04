#ifndef __SINGLY_LL__
#define __SINGLY_LL__

typedef struct _ll_node_t
{
    void *item;
    struct _ll_node_t *next;
} ll_node_t;

typedef struct _ll_t
{
    ll_node_t *head;
    size_t length;
} ll_t;

void ll_create(ll_t **list);
void ll_destroy(ll_t **list);
void ll_clear(ll_t *list, void (*unload_fun)(void *));
void ll_delete_at(ll_t *list, size_t index, void (*unload_fun)(void *));
size_t ll_get_index(const ll_t *list, const void *item, int (*cmp_fun)(const void *, const void *));
void ll_append_front(ll_t *list, const void *item, void (*load_fun)(const void *, void **));
void ll_append_back(ll_t *list, const void *item, void (*load_fun)(const void *, void **));
void ll_insert_at(ll_t *list, const void *item, size_t index, void (*load_fun)(const void *, void **));
void ll_insert_block_at(ll_t *list, size_t index, void (*load_fun)(const void *, void **), size_t count, ...);
void *ll_get_at(const ll_t *list, size_t index);
void ll_replace_at(ll_t *list, size_t index, const void *item, void (*unload_fun)(void *), void (*load_fun)(const void *, void **));
size_t ll_size(const ll_t *list);
void ll_print(const ll_t *list, void (*print_func)(const void *));

#endif /* __SINGLY_LL__ */