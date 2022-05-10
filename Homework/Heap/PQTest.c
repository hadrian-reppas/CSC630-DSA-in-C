#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

#include "PQ.h"
#include "PQTest.h"

#define TEST_LEN 10000

int main() {

    srand(time(NULL));

    test_add_and_poll();
    test_heapify();
}

// Add a bunch of random priorities to a queue.
// Then poll them off making sure that each priority
// is greater than the last.
void test_add_and_poll() {
    int arr[TEST_LEN];
    fill_arr(arr, TEST_LEN);

    struct PQ* pq = make_pq();

    for (int i = 0; i < TEST_LEN; i++)
        add(pq, arr[i], arr[i]);

    int prev = INT_MIN;
    while (pq->size) {
        int data = poll(pq);
        assert(prev <= data);
        prev = data;
    }

    destroy(pq);

    printf("add and poll test passed\n");
}

// Generate an array of pairs with random priorities
// and call heapify on it. Check that the resulting
// heap obeys the heap property.
void test_heapify() {
    int priorities[TEST_LEN];
    fill_arr(priorities, TEST_LEN);

    struct pair* arr = malloc(TEST_LEN*sizeof(struct pair));

    for (int i = 0; i < TEST_LEN; i++) {
        arr[i].priority = priorities[i];
        arr[i].data = 42;
    }

    struct PQ* pq = heapify(arr, TEST_LEN);

    assert_is_heap(pq);

    destroy(pq);

    printf("heapify test passed\n");
}

void assert_is_heap(struct PQ* pq) {
    for (int i = 0; i < pq->size; i++) {
        int c1 = 2*i + 1, c2 = 2*i + 2;
        assert(c1 >= pq->size
            || pq->queue[i].priority <= pq->queue[c1].priority);
        assert(c2 >= pq->size
            || pq->queue[i].priority <= pq->queue[c2].priority);
    }
}

void fill_arr(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand();
}
