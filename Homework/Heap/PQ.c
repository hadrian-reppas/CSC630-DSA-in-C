#include <stdio.h>
#include <stdlib.h>

#include "PQ.h"

int peek(struct PQ* pq) {
    return pq->queue[0].data;
}

void add(struct PQ* pq, int priority, int data) {
    if (pq->size == pq->capacity)
        grow(pq);
    pq->queue[pq->size].priority = priority;
    pq->queue[pq->size].data = data;
    bubble_up(pq, pq->size++);
}

int poll(struct PQ* pq) {
    swap(pq->queue, pq->queue + --pq->size);
    bubble_down(pq, 0);
    if (pq->size < pq->capacity/4)
        shrink(pq);
    return pq->queue[pq->size].data;
}

struct PQ* heapify(struct pair arr[], int len) {
    struct PQ* pq = malloc(sizeof(struct PQ));
    pq->size = len;
    pq->capacity = len;
    pq->queue = arr;
    for (int i = len - 1; i >= 0; i--)
        bubble_down(pq, i);
    return pq;
}

void bubble_up(struct PQ* pq, int index) {
    if (index == 0)
        return;
    int parent = (index - 1)/2;
    if (pq->queue[parent].priority > pq->queue[index].priority) {
        swap(pq->queue + parent, pq->queue + index);
        bubble_up(pq, parent);
    }
}

void bubble_down(struct PQ* pq, int index) {
    int c1 = 2*index + 1;
    if (c1 >= pq->size)
        return;
    int c2 = c1 + 1;
    int mindex;
    if (c2 >= pq->size || pq->queue[c1].priority <= pq->queue[c2].priority)
        mindex = c1;
    else
        mindex = c2;
    if (pq->queue[index].priority > pq->queue[mindex].priority) {
        swap(pq->queue + index, pq->queue + mindex);
        bubble_down(pq, mindex);
    }
}

void grow(struct PQ* pq) {
    pq->capacity *= 2;
    pq->queue = realloc(pq->queue, pq->capacity*sizeof(struct pair));
}

void shrink(struct PQ* pq) {
    if (pq->capacity <= 8)
        return;
    pq->capacity /= 2;
    pq->queue = realloc(pq->queue, pq->capacity*sizeof(struct pair));
}

void swap(struct pair* a, struct pair* b) {
    struct pair temp = *a;
    *a = *b;
    *b = temp;
}

void print(struct PQ* pq) {
    for(int i = 0; i < pq->size; i++)
        printf("(%d: %d)\n", pq->queue[i].priority, pq->queue[i].data);
}

struct PQ* make_pq() {
    struct PQ* pq = malloc(sizeof(struct PQ));
    pq->size = 0;
    pq->capacity = 8;
    pq->queue = malloc(8*sizeof(struct pair));
    return pq;
}

void destroy(struct PQ* pq) {
    free(pq->queue);
    free(pq);
}
