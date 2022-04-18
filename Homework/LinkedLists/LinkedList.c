#include <stdio.h>
#include <stdlib.h> 
#include "LinkedList.h"

#define TAIL (*head)->next
#define TOP (*head)->data

// helper functions
static int min_ii(int a, int b) { return a < b ? a : b; }
static int max_ii(int a, int b) { return a > b ? a : b; }

void push(struct node** head, int data) {
    struct node* to_add = malloc(sizeof(struct node));
    to_add->data = data;
    to_add->next = *head;
    *head = to_add;
}

void pop(struct node** head) {
    struct node* new_head = TAIL;
    free(*head);
    *head = new_head;
}

void insert(struct node** head, int index, int data) {
    if(index)
        insert(&TAIL, index - 1, data);
    else
        push(head, data);
}

void delete(struct node** head, int index) {
    if(index)
        delete(&TAIL, index - 1);
    else
        pop(head);
}

int data_at(struct node** head, int index) {
    if(index)
        return data_at(&TAIL, index - 1);
    else
        return TOP;
}

int sum(struct node** head) {
    if(*head)
        return TOP + sum(&TAIL);
    else
        return 0;
}

int min(struct node** head) {
    if(TAIL)
        return min_ii(TOP, min(&TAIL)); 
    else
        return TOP;
}

int max(struct node** head) {
    if(TAIL)
        return max_ii(TOP, max(&TAIL)); 
    else
        return TOP;
}

void reverse(struct node** head) {
    if(*head == NULL || TAIL == NULL) 
        return; // 0 or 1 elements in list, do nothing
    struct node* tail = TAIL;
    reverse(&tail);
    TAIL->next = *head;
    TAIL = NULL;
    *head = tail;
}

void destroy(struct node** head) {
    if(*head) {
        destroy(&TAIL);
        free(*head);
        *head = NULL;
    }
}

void print(struct node** head) {
    if(*head) {
        printf("%d ", TOP);
        print(&TAIL);
    } else {
        printf("\n");
    }
}

void push_array(struct node** head, int data[], int n) {
    for(int i = n - 1; i >= 0; i--)
        push(head, data[i]);
}
