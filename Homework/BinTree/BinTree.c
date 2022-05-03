#include <stdio.h>
#include <stdlib.h> 
#include "BinTree.h"

#include <stdio.h>

#define LEFT ((*proot)->left)
#define RIGHT ((*proot)->right)
#define KEY ((*proot)->key)
#define DATA ((*proot)->data)

void add(struct node** proot, int key, int data) {
    if (*proot) {
        if (key > KEY)
            add(&RIGHT, key, data);
        else
            add(&LEFT, key, data);
    } else {
        *proot = malloc(sizeof(struct node));
        KEY = key;
        DATA = data;
        LEFT = NULL;
        RIGHT = NULL;
    }
}

void print(struct node** proot) {
    if (*proot) {
        print(&LEFT);
        printf("%d: %d\n", KEY, DATA);
        print(&RIGHT);
    }
}

void lisp_print(struct node** proot) {
    if (*proot) {
        printf("(%d ", KEY);
        lisp_print(&LEFT);
        lisp_print(&RIGHT);
        printf(")");
    } else {
        printf(" NULL ");
    }
}

void delete(struct node** proot, int key) {
    if (key == KEY) {
        if (LEFT && RIGHT) {
            struct node** largest = find_largest(&LEFT);
            KEY = (*largest)->key;
            DATA = (*largest)->data;
            delete(largest, (*largest)->key);
        } else if (LEFT) {
            struct node* grandchild = LEFT;
            free(*proot);
            *proot = grandchild;
        } else {
            struct node* grandchild = RIGHT;
            free(*proot);
            *proot = grandchild;
        }
    } else if (key < KEY) {
        delete(&LEFT, key);
    } else {
        delete(&RIGHT, key);
    }
}

int contains(struct node** proot, int key) {
    if (*proot == NULL)
        return 0;
    else if (key == KEY)
        return 1;
    else if (key < KEY)
        return contains(&LEFT, key);
    else
        return contains(&RIGHT, key);
}

int get(struct node** proot, int key) {
    if (key == KEY)
        return DATA;
    else if (key < KEY)
        return get(&LEFT, key);
    else
        return get(&RIGHT, key);
}

void change(struct node** proot, int key, int new_data) {
    if (key == KEY)
        DATA = new_data;
    else if (key < KEY)
        change(&LEFT, key, new_data);
    else
        change(&RIGHT, key, new_data);
}

void destroy(struct node** proot) {
    if (*proot == NULL) 
        return;
    destroy(&LEFT);
    destroy(&RIGHT);
    free(*proot);
    *proot = NULL;
}

struct node* prev = NULL;

void to_ll(struct node** proot) {
    if (*proot == NULL)
        return;

    to_ll(&RIGHT);
    to_ll(&LEFT);
    RIGHT = prev;
    LEFT = NULL;
    prev = *proot;
}

void double_ll(struct node** proot) {
    if (*proot == NULL || RIGHT == NULL)
        return;
    RIGHT->left = *proot;
    double_ll(&RIGHT);
}

struct node** find_largest(struct node** proot) {
    if (RIGHT)
        return find_largest(&RIGHT);
    return proot;
}
