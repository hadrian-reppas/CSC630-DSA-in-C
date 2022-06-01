
#ifdef STR_KEY
  #define KEY_TYPE char*
  #define EQ(a, b) !strcmp(a, b)
#else
  #define KEY_TYPE int
  #define EQ(a, b) a == b
#endif

struct node {
    KEY_TYPE key;
    int value;
    struct node* next;
};

struct hash_map {
    int size;
    int n_buckets;
    int mask;
    struct node** buckets;
};

int hash(struct hash_map* map, KEY_TYPE x);
void add(struct hash_map* map, KEY_TYPE key, int value);
int get(struct hash_map* map, KEY_TYPE key);
int contains(struct hash_map* map, KEY_TYPE key);
void edit(struct hash_map* map, KEY_TYPE key, int new_value);
void delete(struct hash_map* map, KEY_TYPE key);
void print(struct hash_map* map);
void grow(struct hash_map* map);
void shrink(struct hash_map* map);
struct hash_map* make_hash_map();
void destroy(struct hash_map* map);
void destroy_ll(struct node* cur);
