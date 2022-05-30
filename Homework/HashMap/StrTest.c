#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#define STR_KEY

#include "HashMap.h"
#include "StrTest.h"

#define TEST_LEN 1000

int main() {

    srand(time(NULL));

    test_add_and_get();
    test_contains_and_delete();
    test_edit();

    return 0;
}

// Add a bunch of random keys. Then loop over each
// key make sure the value is what we expect.
void test_add_and_get() {
    char arr[TEST_LEN*STR_LEN];
    fill_arr(arr, TEST_LEN, STR_LEN);

    struct hash_map* map = make_hash_map();

    for (int i = 0; i < TEST_LEN*STR_LEN; i += STR_LEN)
        add(map, arr + i, i);

    for (int i = 0; i < TEST_LEN*STR_LEN; i += STR_LEN)
        assert(get(map, arr + i) == i);

    destroy(map);

    printf("add and get test passed\n");
}

// Add a bunch of random keys. Then loop over each
// key and make sure it is in the map. Finally delete
// the key and make sure it is not in the map.
void test_contains_and_delete() {
    char arr[TEST_LEN*STR_LEN];
    fill_arr(arr, TEST_LEN, STR_LEN);

    struct hash_map* map = make_hash_map();

    for (int i = 0; i < TEST_LEN*STR_LEN; i += STR_LEN)
        add(map, arr + i, 0);

    for (int i = 0; i < TEST_LEN*STR_LEN; i += STR_LEN) {
        assert(contains(map, arr + i));
        delete(map, arr + i);
        assert(!contains(map, arr + i));
    }

    destroy(map);

    printf("contains and delete test passed\n");
}

// Add a bunch of random keys and values. Then loop
// over each key and change the value to value - 1.
// Finally, use get() to check that values are correct
void test_edit() {
    char arr[TEST_LEN*STR_LEN];
    fill_arr(arr, TEST_LEN, STR_LEN);

    struct hash_map* map = make_hash_map();

    for (int i = 0; i < TEST_LEN*STR_LEN; i += STR_LEN)
        add(map, arr + i, i);

    for (int i = 0; i < TEST_LEN*STR_LEN; i += STR_LEN)
        edit(map, arr + i, i - 1);

    for (int i = 0; i < TEST_LEN*STR_LEN; i += STR_LEN)
        assert(get(map, arr + i) == i - 1);
    
    destroy(map);

    printf("edit test passed\n");
}

// A bit complicated because I want to avoid duplicates...
void fill_arr(char arr[], int size, int len) {
    int c = (rand() >> 12) % 16 + 1;
    int m = (rand()*rand()*rand()) & 0xffffff;
    for (int i = 0; i < size*len; i += len) {
        sprintf(arr + i, "%d", i*c + m);
        int j = i - 1;
        while (arr[++j]) {
            if (random() % 2 == 0)
                arr[j] += 49;
            else
                arr[j] += 59;
        }
    }
}