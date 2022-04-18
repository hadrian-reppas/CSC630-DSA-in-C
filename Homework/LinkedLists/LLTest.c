#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "LinkedList.h"
#include "LLTest.h"

#define TEST_LEN 1000
#define MAX_DATA 256

int main(int argc, char** argv) {

    srand(time(NULL));

    test_push_and_pop();
    test_insert();
    test_delete();
    test_data_at();
    test_sum();
    test_min();
    test_max();
    test_reverse();

    return 0;
}

// Pushes random integers onto a list and
// pops them off making sure they come off
// in the same order we put them on.
void test_push_and_pop() {
    struct node* head = NULL;
    
    int data[TEST_LEN];
    fill_rand_array(data, TEST_LEN);

    push_array(&head, data, TEST_LEN);

    for(int i = 0; i < TEST_LEN; i++) {
        assert(head->data == data[i]);
        pop(&head);
    }

    printf("push and pop test passed\n");
}

// Zips two arrays into a list by inserting
// elements at every other index. Make sure
// this gives us what we expect.
void test_insert() {
    struct node* head = NULL;

    int evens[TEST_LEN];
    int odds[TEST_LEN];
    fill_rand_array(evens, TEST_LEN);
    fill_rand_array(odds, TEST_LEN);

    push_array(&head, odds, TEST_LEN);
   
    for(int i = 0; i < TEST_LEN; i++)
        insert(&head, 2*i, evens[i]);
    
    for(int i = 0; i < 2*TEST_LEN; i++) {
        if(i & 1)
            assert(head->data == odds[i/2]);
        else
            assert(head->data == evens[i/2]);
        pop(&head);
    }

    printf("insert test passed\n");
}

// Fill a list with random elements then delete
// every other element. Make sure the resulting
// list is what we expect.
void test_delete() {
    struct node* head = NULL;

    int data[TEST_LEN];
    fill_rand_array(data, TEST_LEN);

    push_array(&head, data, TEST_LEN);
   
    for(int i = 0; i < TEST_LEN/2; i++)
        delete(&head, i + 1);

    for(int i = 0; i < TEST_LEN/2; i++) {
        assert(head->data == data[2*i]);
        pop(&head);
    }
    
    printf("delete test passed\n"); 
}

// Pushed a bunch of random integers onto
// a list. Access each element with data_at()
// and make sure it is what we expect.
void test_data_at() {
    struct node* head = NULL;

    int data[TEST_LEN];
    fill_rand_array(data, TEST_LEN);

    push_array(&head, data, TEST_LEN);
   
    for(int i = 0; i < TEST_LEN; i++)
        assert(data_at(&head, i) == data[i]);

    printf("data_at test passed\n");
}

// Pushes a bunch of random integers onto
// a list while summing them on our own.
// Then call the sum function and make
// sure the sums match.
void test_sum() {
    struct node* head = NULL;

    int data[TEST_LEN];
    fill_rand_array(data, TEST_LEN);

    push_array(&head, data, TEST_LEN);

    int our_sum = 0;
    for(int i = 0; i < TEST_LEN; i++)
        our_sum += data[i];

    assert(our_sum == sum(&head));

    printf("sum test passed\n");
}

// Pushes a bunch of random integers onto
// a list while keeping track of the smallest
// on our own. Then call the min function
// and make sure the numbers match.
void test_min() {
    struct node* head = NULL;

    int data[TEST_LEN];
    fill_rand_array(data, TEST_LEN);

    push_array(&head, data, TEST_LEN);

    int our_min = MAX_DATA;
    for(int i = 0; i < TEST_LEN; i++)
        our_min = data[i] < our_min ? data[i] : our_min;

    assert(our_min == min(&head));

    printf("min test passed\n");
}

// Pushes a bunch of random integers onto
// a list while keeping track of the biggest
// on our own. Then call the max function
// and make sure the numbers match.
void test_max() {
    struct node* head = NULL;

    int data[TEST_LEN];
    fill_rand_array(data, TEST_LEN);

    push_array(&head, data, TEST_LEN);

    int our_max = 0;
    for(int i = 0; i < TEST_LEN; i++)
        our_max = data[i] > our_max ? data[i] : our_max;

    assert(our_max == max(&head));

    printf("max test passed\n");
}

// Pushes a bunch of random integers onto
// a list and reverses it, making sure we
// get what we expect.
void test_reverse() {
    struct node* head = NULL;

    int data[TEST_LEN];
    fill_rand_array(data, TEST_LEN);

    push_array(&head, data, TEST_LEN);

    reverse(&head);

    for(int i = TEST_LEN - 1; i >= 0; i--) {
        assert(head->data == data[i]);
        pop(&head);
    }

    printf("reverse test passed\n");
}

void fill_rand_array(int arr[], int n) {
    for(int i = 0; i < n; i++)
        arr[i] = rand() % MAX_DATA;
}
