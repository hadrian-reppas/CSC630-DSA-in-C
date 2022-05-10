struct pair {
    int priority;
    int data;
};

struct PQ {
    int size;
    int capacity;
    struct pair* queue;
};

int peek(struct PQ* pq);
void add(struct PQ* pq, int priority, int data);
int poll(struct PQ* pq);
struct PQ* heapify(struct pair arr[], int len);
void bubble_up(struct PQ* pq, int index);
void bubble_down(struct PQ* pq, int index);
void grow(struct PQ* pq);
void shrink(struct PQ* pq);
void swap(struct pair* a, struct pair* b);
void print(struct PQ* pq);
struct PQ* make_pq();
void destroy(struct PQ* pq);
