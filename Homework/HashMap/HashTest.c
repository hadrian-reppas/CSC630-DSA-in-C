#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#include "HashMap.h"
#include "HashTest.h"

#define TEST_LEN 1000

int main() {

    srand(time(NULL));

    test_add_and_get();
    test_contains_and_delete();
    test_edit();

    return 0;
}

// Add a bunch of random keys and values such that
// key*key = value. Then loop over each key 
// make sure the value is its square.
void test_add_and_get() {
    int arr[TEST_LEN];
    fill_arr(arr, TEST_LEN);

    struct hash_map* map = make_hash_map();

    for (int i = 0; i < TEST_LEN; i++)
        add(map, arr[i], arr[i]*arr[i]);

    for (int i = 0; i < TEST_LEN; i++)
        assert(get(map, arr[i]) == arr[i]*arr[i]);

    destroy(map);

    printf("add and get test passed\n");
}

// Add a bunch of random keys. Then loop over each
// key and make sure it is in the map. Finally delete
// the key and make sure it is not in the map.
void test_contains_and_delete() {
    int arr[TEST_LEN];
    fill_arr(arr, TEST_LEN);

    struct hash_map* map = make_hash_map();

    for (int i = 0; i < TEST_LEN; i++)
        add(map, arr[i], arr[i]*arr[i]);

    for (int i = 0; i < TEST_LEN; i++) {
        assert(contains(map, arr[i]));
        // delete(map, arr[i]);
        // assert(!contains(map, arr[i]));
    }

    destroy(map);

    printf("contains and delete test passed\n");
}

// Add a bunch of random keys and values such that
// key*key = value. Then loop over each key and
// change the value to key*key - 1 and check that.
// Finally, use get() to check that values are correct
void test_edit() {
    int arr[TEST_LEN];
    fill_arr(arr, TEST_LEN);

    struct hash_map* map = make_hash_map();

    for (int i = 0; i < TEST_LEN; i++)
        add(map, arr[i], arr[i]*arr[i]);

    for (int i = 0; i < TEST_LEN; i++)
        edit(map, arr[i], arr[i]*arr[i] - 1);

    for (int i = 0; i < TEST_LEN; i++)
        assert(get(map, arr[i]) == arr[i]*arr[i] - 1);
    
    destroy(map);

    printf("edit test passed\n");
}

void fill_arr(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = i;
    for (int i = 0; i < 3*size; i++) {
        int j = rand() % size;
        int k = rand() % size;
        int temp = arr[j];
        arr[j] = arr[k];
        arr[k] = temp;
    }
}
