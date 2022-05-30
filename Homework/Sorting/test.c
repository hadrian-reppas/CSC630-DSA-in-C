#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "sorting.h"
#include "test.h"

#define TEST_TIME 2

int test_lens[] = {20, 50, 100, 500, 1000, 5000, 10000, 50000};

int main() {

    srand(time(NULL));

    printf("              \t20\t50\t100\t500\t1000\t5000\t10000\t50000\n");
    printf("--------------------------------------------------------------------------------\n");
    test_sort(insertion_sort, "insertion sort");
    test_sort(merge_sort, "    merge sort");
    test_sort(heap_sort, "     heap sort");
    test_sort(quick_sort, "    quick sort");
    test_sort(radix_sort, "    radix sort");

    return 0;
}

// Takes a sorting function, runs it as many times as possible
// in TEST_TIME seconds. Then prints the average time.
void test_sort(void(*sort)(int*, int), char* name) {
    int arr[50000];
    printf("%s", name);

    for (int i = 0; i < 8; i++) {
        time_t start = time(NULL);
        long timer = 0;
        int n = 0;
        while (time(NULL) - start < TEST_TIME) {
            fill_array(arr, test_lens[i]);
            start_timer();
            sort(arr, test_lens[i]);
            timer += stop_timer();
            assert_is_sorted(arr, test_lens[i]);
            n++;
        }
        printf("\t%ld", timer/(1000 * n));
        fflush(stdout);
    }
    printf("\n");
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

