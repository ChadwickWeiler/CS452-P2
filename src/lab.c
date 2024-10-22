#include "lab.h"
#include <stdio.h>
#include <stdlib.h>


//Creating the structure of a simple linked list
typedef struct Node{
    int object; 
    struct Node* next;
} Node;

typedef struct queue_t{
    int size;
    Node* head;
    Node* tail;
} queue_t;


queue_t queue_init(int capacity){
    queue_t new_q;
    new_q.size = capacity;
    new_q.head = NULL;
    new_q.tail = NULL;
}


void queue_destroy(queue_t q);


void enqueue(queue_t q, void *data);


void *dequeue(queue_t q);


void queue_shutdown(queue_t q);



bool is_empty(queue_t q){
    if(q[0] != NULL){
        return false;
    }
    else{
        return true;
    }
}

bool is_shutdown(queue_t q);