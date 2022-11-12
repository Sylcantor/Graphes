#ifndef _PRIORITE_

#define _PRIORITE_

#include <stdio.h>
#include <stdlib.h>

typedef struct pqueue {
    int capacity;
    int size;
    float *value;
    int *present; // boolean
} pqueue;

/**
 * Create a new priority queue
 * @param n the number of elements in the queue
*/

void init_pqueue(pqueue *q, int n);

/**
 * Add an element to the queue
 * @param q the queue
 * @param i the element to add
 * @param value the value of the element
 * @return 1 if the element was added, 0 if the queue is full
*/
void update_pqueue(pqueue *q, int i, float v);

/**
 * Check if the queue is empty
 * @param q the queue
 * @return 1 if the queue is empty, 0 otherwise
*/
int isempty_pqueue(pqueue *q);

/**
 * Remove the element with the highest priority from the queue
 * @param q the queue
 * @return the value of the element
*/
int extractmin_pqueue(pqueue *q);

/**
 * Free the memory used by the queue
 * @param q the queue
*/  
void free_pqueue(pqueue *q);


#endif