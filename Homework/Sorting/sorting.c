#include <stdlib.h>
#include <string.h>

#include "sorting.h"

int* scratch;
int scratch_size = 0;

void insertion_sort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            swap(arr + j, arr + j - 1);
            j--;
        }
    }
}

void heap_sort(int arr[], int size) {
    for (int i = size - 1; i >= 0; i--)
        bubble_down(arr, size, i);
    for (int i = 0; i < size; i++) {
        swap(arr, arr + size - 1 - i);
        bubble_down(arr, size - 1 - i, 0);
    }
}

void merge_sort(int arr[], int size) {
    if (size < 2)
        return;

    if (scratch_size == 0) {
        scratch = malloc(size*sizeof(int));
        scratch_size = size;
    }

    int mid = size / 2;

    merge_sort(arr, mid);
    merge_sort(arr + mid, size - mid);

    merge(arr, mid, arr + mid, size - mid);

    if (size == scratch_size) {
        free(scratch);
        scratch_size = 0;
    }
}

void quick_sort(int arr[], int size) {
    if (size < 2)
        return;

    if (scratch_size == 0) {
        scratch = malloc(size*sizeof(int));
        scratch_size = size;
    }

    int small_size = partition(arr, size);

    quick_sort(arr, small_size);
    quick_sort(arr + small_size + 1, size - small_size - 1);

    if (size == scratch_size) {
        free(scratch);
        scratch_size = 0;
    }
}

void radix_sort(int arr[], int size) {
    scratch = malloc(size*sizeof(int));
    radix_pass(arr, scratch, size, 0);
    radix_pass(scratch, arr, size, 8);
    radix_pass(arr, scratch, size, 16);
    radix_pass(scratch, arr, size, 24);
    free(scratch);
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubble_down(int arr[], int size, int index) {
    int c1 = 2*index + 1;
    if (c1 >= size)
        return;
    int c2 = c1 + 1;
    int max_index;
    if (c2 >= size || arr[c1] >= arr[c2])
        max_index = c1;
    else
        max_index = c2;
    if (arr[index] < arr[max_index]) {
        swap(arr + index, arr + max_index);
        bubble_down(arr, size, max_index);
    }
}

void merge(int a[], int a_size, int b[], int b_size) {
    int i = 0, j = 0, k = 0;
    while (i < a_size || j < b_size) {
        if (i < a_size && (j == b_size || a[i] <= b[j]))
            scratch[k++] = a[i++];
        else
            scratch[k++] = b[j++];
    }
    memcpy(a, scratch, k*sizeof(int));
}

int partition(int arr[], int size) {
    int pivot = arr[0];

    int low = 0, high = size - 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] < pivot)
            scratch[low++] = arr[i];
        else
            scratch[high--] = arr[i];
    }

    scratch[low] = pivot;

    memcpy(arr, scratch, size*sizeof(int));

    return low;
}

void radix_pass(int input[], int output[], int size, int offset) {
    int counts[256];
    memset(counts, 0, 256*sizeof(int));
    for (int i = 0; i < size; i++)
        counts[(input[i] >> offset) & 0xff]++;
    for (int i = 1; i < 256; i++)
        counts[i] += counts[i - 1];
    for (int i = size - 1; i >= 0; i--) {
        int j = --counts[(input[i] >> offset) & 0xff];
        output[j] = input[i];
    }
}
