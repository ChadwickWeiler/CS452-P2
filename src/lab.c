#include "lab.h"
#include <stdio.h>
#include <stdlib.h>


//Creating the structure of a simple doubly linked list
typedef struct Node{
    int data; 
    struct Node* oldest;
    struct Node* newest;    
} Node;

typedef struct queue_t{
    int size;
    int max_size;
    Node* head;
    Node* tail;
} queue_t;


queue_t queue_init(int capacity){
    
    queue_t new_q;
    new_q.size = 0;
    new_q.max_size = capacity;
    new_q.head = NULL;
    new_q.tail = NULL;

    return new_q;
}


void queue_destroy(queue_t q);


void enqueue(queue_t q, void *data){

Node* n = (Node*)malloc(sizeof(Node));
    if(q.size < q.max_size){

            n->data = *(int*)data;

            if(q.size != 0){
            q.tail->newest = n;
            q.tail = n; 
            }

            else{
            q.head = n;
            q.tail = n;
            n->newest = NULL;
            n->oldest = NULL;
            }

            q.size ++;
        }
    return q;
}

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