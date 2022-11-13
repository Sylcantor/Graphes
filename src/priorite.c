


#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "priorite.h"

#define INFINITY 1000000000 // a revoir

void init_pqueue(pqueue *q, int n){
    q->capacity = n;
    q->size = 0;
    if ((q->value = (float *) malloc(n * sizeof(float))) == NULL) {
        report_error("malloc() error");	
    }
    if ((q->present = (int *) malloc(n * sizeof(int))) == NULL) {
        report_error("malloc() error");	
    }
    for(int i=0; i<n; i++){
        q->value[i] = INFINITY;
        q->present[i] = 0;
    }
}


void update_pqueue(pqueue *q, int i, float v){
    q->value[i] = v;
    q->present[i] = 1;
    q->size++;
}

int isempty_pqueue(pqueue *q){
    return q->size == 0;
}

int extractmin_pqueue(pqueue *q){
    int min=0;
    for(int i=0; i<q->capacity; i++){
        if(q->present[i] == 1){
            min = i;
            break;
        }
    }
    for(int i=0; i<q->capacity; i++){
        if(q->present[i] && q->value[i] < q->value[min]){
            min = i;
        }
    }
    q->present[min] = 0;
    q->size--;
    return min;
}

void free_pqueue(pqueue *q){
    free(q->value);
    free(q->present);
}