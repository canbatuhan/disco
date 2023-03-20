#include <stdlib.h>
#include <string.h>
#include "../include/queue.h"

/**
 * @brief Initializes a queue
 * 
 * @param capacity capacity of the queue
 * @return disco_queue* pointer to the queue
 */
disco_queue* init_queue(int capacity) {
    disco_queue* ptr = (disco_queue*) malloc(sizeof(disco_queue));
    ptr->head = NULL;
    ptr->tail = NULL;
    ptr->size = 0;
    if (capacity <= MAX_QUEUE_CAPACITY) {
        ptr->capacity = capacity;
    } else {
        ptr->capacity = MAX_QUEUE_CAPACITY;
    }
    return ptr;
}

/**
 * @brief Enqueue data into the queue
 * 
 * @param ptr pointer to the queue
 * @param data constant char array
 */
void enqueue(disco_queue* ptr, const char* data) {
    /* Initial case */
    if (ptr->size == 0) {
        ptr->head = (disco_queue_node*) malloc(sizeof(disco_queue_node));
        ptr->head->data = data;
        ptr->tail = ptr->head;
        ptr->head->next = ptr->tail;
        ptr->size++;
    }
    
    /* General case */
    else if (ptr->size < ptr->capacity) { 
        ptr->tail->next = (disco_queue_node*) malloc(sizeof(disco_queue_node));
        ptr->tail->next->data = data;
        ptr->tail = ptr->tail->next;
        ptr->size++;
    }

    /* Do nothing if full */
}

/**
 * @brief Dequeue data from the queue
 * 
 * @param ptr pointer to the queue
 * @return const char* constant char array
 */
const char* dequeue(disco_queue* ptr) {
    if (ptr->size > 0) {
        /* Extract data */
        char* data = (char*) malloc(strlen(ptr->head->data));
        strcpy(data, ptr->head->data);
        
        /* Delete node */
        disco_queue_node* temp = ptr->head;
        ptr->head = ptr->head->next;
        free(temp);

        /* Decrement size and return */
        ptr->size--;
        return data;
    }

    /* Return NULL if fails */
    return NULL;
}

/**
 * @brief Clears a queue completely
 * 
 * @param ptr pointer to a queue
 */
void delete_queue(disco_queue* ptr) {
    int count;
    for (count=0; count<ptr->size; ) {
        dequeue(ptr); // Dequeue all the nodes
    }
}