struct node {
    int key;
    int value;
    struct node* next;
};

struct hash_map {
    int size;
    int n_buckets;
    int mask;
    struct node** buckets;
};

int hash(struct hash_map* map, int x);
void add(struct hash_map* map, int key, int value);
int get(struct hash_map* map, int key);
int contains(struct hash_map* map, int key);
void edit(struct hash_map* map, int key, int new_value);
void delete(struct hash_map* map, int key);
void print(struct hash_map* map);
void grow(struct hash_map* map);
void shrink(struct hash_map* map);
struct hash_map* make_hash_map();
void destroy(struct hash_map* map);
