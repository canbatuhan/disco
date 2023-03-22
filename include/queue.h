#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

#define MAX_QUEUE_CAPACITY 512

typedef struct node {
    const char * data;
    struct node* next;
} disco_queue_node;

typedef struct queue {
    struct node* head;
    struct node* tail;
    size_t size;
    size_t capacity;
} disco_queue;

disco_queue* init_queue(int queue_capacity);
void enqueue(disco_queue* ptr, const char* data);
const char* dequeue(disco_queue* ptr);
void delete_queue(disco_queue* ptr);

#endif