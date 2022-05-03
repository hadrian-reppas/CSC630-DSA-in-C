struct node {
    int key;
    int data;
    struct node* left;
    struct node* right;
};

void add(struct node** proot, int key, int data);
int contains(struct node** proot, int key);
void print(struct node** proot);
int get(struct node** proot, int key);
void delete(struct node** proot, int key);
void change(struct node** proot, int key, int new_data);
void destroy(struct node** proot);
void to_ll(struct node** proot);
void double_ll(struct node** proot);
void lisp_print(struct node** proot);

struct node** find_largest(struct node** root);
