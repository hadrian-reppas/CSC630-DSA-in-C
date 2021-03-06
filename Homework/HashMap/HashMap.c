#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "HashMap.h"

#ifdef STR_KEY
int hash(struct hash_map* map, char* x) {
    int h = 0;
    int p = 1;
    while (*x) {
        h += p**x;
        p *= 31;
    }
    return map->mask & h;
}
#else
int hash(struct hash_map* map, int x) {
    int h = x*x ^ 0x73463293;
    return map->mask & h;
}
#endif

void add(struct hash_map* map, KEY_TYPE key, int value) {
    if (map->size >= map->n_buckets)
        grow(map);
    int h = hash(map, key);
    struct node* cur = malloc(sizeof(struct node));
    cur->key = key;
    cur->value = value;
    cur->next = map->buckets[h];
    map->buckets[h] = cur;
    map->size++;
}

int get(struct hash_map* map, KEY_TYPE key) {
    int h = hash(map, key);
    struct node* cur = map->buckets[h];
    while (1) {
        if (EQ(cur->key, key))
            return cur->value;
        cur = cur->next;
    }
}

int contains(struct hash_map* map, KEY_TYPE key) {
    int h = hash(map, key);
    struct node* cur = map->buckets[h];
    while (cur) {
        if (EQ(cur->key, key))
            return 1;
        cur = cur->next;
    }
    return 0;
}

void edit(struct hash_map* map, KEY_TYPE key, int new_value) {
    int h = hash(map, key);
    struct node* cur = map->buckets[h];
    while (cur) {
        if (EQ(cur->key, key)) {
            cur->value = new_value;
            return;
        }
        cur = cur->next;
    }
}

void delete(struct hash_map* map, KEY_TYPE key) {
    if (2*map->size < map->n_buckets)
        shrink(map);
    map->size--;
    int h = hash(map, key);
    if (EQ(map->buckets[h]->key, key)) {
        struct node* n = map->buckets[h];
        map->buckets[h] = n->next;
        free(n);
        return;
    }
    struct node* prev = map->buckets[h];
    struct node* cur = prev->next;
    while (1) {
        if (EQ(cur->key, key)) {
            prev->next = cur->next;
            free(cur);
            return;
        }
        prev = prev->next;
        cur = cur->next;
    }
}

void print(struct hash_map* map) {
    for (int i = 0; i < map->n_buckets; i++) {
        struct node* cur = map->buckets[i];
        while (cur) {
#ifdef STR_KEY
            printf("(%s: %d)\n", cur->key, cur->value);
#else
            printf("(%d: %d)\n", cur->key, cur->value);
#endif
            cur = cur->next;
        }
    }
}

void grow(struct hash_map* map) {
    struct node** old_buckets = map->buckets;
    int old_n_buckets = map->n_buckets;

    map->size = 0;
    map->n_buckets *= 2;
    map->mask = (map->mask << 1) | 1;
    map->buckets = malloc(map->n_buckets*sizeof(struct node*));
    memset(map->buckets, 0, map->n_buckets*sizeof(struct node*));

    for (int i = 0; i < old_n_buckets; i++) {
        struct node* cur = old_buckets[i];
        while (cur) {
            add(map, cur->key, cur->value); 
            cur = cur->next;
        }
    }

    free(old_buckets);
}

void shrink(struct hash_map* map) {
    if (map->n_buckets <= 16)
        return;

    struct node** old_buckets = map->buckets;
    int old_n_buckets = map->n_buckets;

    map->size = 0;
    map->n_buckets /= 2;
    map->mask = map->mask >> 1;
    map->buckets = malloc(map->n_buckets*sizeof(struct node*));
    memset(map->buckets, 0, map->n_buckets*sizeof(struct node*));

    for (int i = 0; i < old_n_buckets; i++) {
        struct node* cur = old_buckets[i];
        while (cur) {
            add(map, cur->key, cur->value); 
            cur = cur->next;
        }
    }

    free(old_buckets);
}

struct hash_map* make_hash_map() {
    struct hash_map* map = malloc(sizeof(struct hash_map));
    map->size = 0;
    map->n_buckets = 16;
    map->mask = 0xf;
    map->buckets = malloc(16*sizeof(struct node*));
    memset(map->buckets, 0, 16*sizeof(struct node*));
    return map;
}

void destroy(struct hash_map* map) {
    for (int i = 0; i < map->n_buckets; i++)
        destroy_ll(map->buckets[i]);
    free(map->buckets);
    free(map);
}

void destroy_ll(struct node* cur) {
    if (cur) {
        destroy_ll(cur->next);
        free(cur);
    }
}
