#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include "BinTree.h"
#include "BinTest.h"

#define TEST_LEN 10

int main(int argc, char** argv) {

    srand(time(NULL));

    test_add_remove_and_contains();
    test_get_and_change();
    test_to_ll();
}

// Fill a tree with random keys then iterate over the
// keys we added calling contains() to make sure the
// key is in the tree. Then call remove() and call
// contains() again to make sure the key is no longer
// in the tree.
void test_add_remove_and_contains() {

    struct node* root = NULL;

    int keys[TEST_LEN];
    fill_array(keys, TEST_LEN);

    for (int i = 0; i < TEST_LEN; i++)
        add(&root, keys[i], 0);

    for (int i = TEST_LEN - 1; i >= 0; i--) {
        assert(contains(&root, keys[i]));
        delete(&root, keys[i]);
        assert(!contains(&root, keys[i]));
    }

    assert(!contains(&root, -1));
    assert(!contains(&root, TEST_LEN));

    printf("add, remove, and contains test passed\n");
}

// Fill a tree with random keys and values then iterate 
// over the keys we added calling get() to make sure the
// value is correct. Then call change() and call
// get() again to make sure the new value is correct.
void test_get_and_change() {

    struct node* root = NULL;

    int keys[TEST_LEN];
    fill_array(keys, TEST_LEN);

    for (int i = 0; i < TEST_LEN; i++)
        add(&root, keys[i], keys[i] + 1);

    for (int i = TEST_LEN - 1; i >= 0; i--) {
        assert(get(&root, keys[i]) == keys[i] + 1);
        change(&root, keys[i], keys[i] - 1);
        assert(get(&root, keys[i]) == keys[i] - 1);
    }

    printf("get and change test passed\n");
}

// Fill a tree with random keys and turn the tree
// into a linked list. Walk the link list and make
// sure we did not loose or gain elements during
// the conversion.
void test_to_ll() {

    struct node* root = NULL;

    int keys[TEST_LEN];
    fill_array(keys, TEST_LEN);

    for (int i = 0; i < TEST_LEN; i++)
        add(&root, keys[i], keys[i] + 1);

    to_ll(&root);
    double_ll(&root);

    char seen[TEST_LEN];
    memset(seen, 0, TEST_LEN);

    struct node* cur = root;

    for (int i = 0; i < TEST_LEN; i++) {
        assert(!seen[cur->key]);
        seen[cur->key] = 1;
        cur = cur->right;
    }

    assert(cur == NULL);
    for (int i = 0; i < TEST_LEN; i++)
        assert(seen[i]);

    printf("to_ll test passed\n");
}

void fill_array(int* arr, int len) {
    for (int i = 0; i < len; i++)
        arr[i] = i;

    for (int i = 0; i < 3*len; i++) {
        int j = rand() % len, k = rand() % len;
        int temp = arr[j];
        arr[j] = arr[k];
        arr[k] = temp;
    }
}

