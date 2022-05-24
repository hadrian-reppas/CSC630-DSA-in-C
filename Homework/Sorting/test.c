#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "sorting.h"
#include "test.h"

#define TEST_LEN 50000
#define TEST_TIME 2

int main() {

    srand(time(NULL));

    test_sort(insertion_sort, "insertion sort");
    test_sort(merge_sort, "merge sort");
    test_sort(heap_sort, "heap sort");
    test_sort(quick_sort, "quick sort");
    test_sort(radix_sort, "radix sort");


    return 0;
}

void test_sort(void(*sort)(int*, int), char* name) {
    time_t start = time(NULL);
    long timer = 0;
    int arr[TEST_LEN];
    int n = 0;

    while (time(NULL) - start < TEST_TIME) {
        fill_array(arr, TEST_LEN);
        start_timer();
        sort(arr, TEST_LEN);
        timer += stop_timer();
        assert_is_sorted(arr, TEST_LEN);
        n++;
    }

    printf("%s on array of length %d: %ld μs\n", name, TEST_LEN, timer/(1000*n));
}

long start;

void start_timer() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    start = ts.tv_sec * 1000000000 + ts.tv_nsec;
}

long stop_timer() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    long end = ts.tv_sec * 1000000000 + ts.tv_nsec;
    return end - start;
}

void fill_array(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 1000;
}

void assert_is_sorted(int arr[], int size) {
    for (int i = 0; i < size - 1; i++)
        assert(arr[i] <= arr[i + 1]);
}

