struct node
{
    int data;
    struct node* next;
};

void push(struct node** head, int data);
void pop(struct node** head);
void insert(struct node** head, int index, int data);
void delete(struct node** head, int index);
int data_at(struct node** head, int index);
int sum(struct node** head);
int min(struct node** head);
int max(struct node** head);
void reverse(struct node** head);
void destroy(struct node** head);
void print(struct node** head);
void push_array(struct node** head, int* data, int n);
