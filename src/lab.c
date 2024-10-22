#include "lab.h"
#include <stdio.h>
#include <stdlib.h>


//Creating the structure of a simple doubly linked list
typedef struct Node{
    void *data; 
    struct Node* next;
    struct Node* prev;    
} Node;

typedef struct queue{
    int size;
    int max_size;
    Node* head;
    Node* tail;
    Node* temp;

    bool sd;

} queue;


queue_t queue_init(int capacity){
    
    queue_t new_q = (queue_t)malloc(sizeof(struct queue));
        if(new_q == NULL){
            printf("no data provided");
            free(new_q);
            return NULL;
        }

    new_q->size = 0;
    new_q->max_size = capacity;
    new_q->head = NULL;
    new_q->tail = NULL;
    new_q->temp = NULL;
    new_q->sd = false;

    return new_q;
}


void queue_destroy(queue_t q){

    if(is_empty(q)){
        //print out error statement for empty queue
    }

    while(q->size > 0){
        if(q->size != 1){
            q->head = q->head->prev;
            free(q->head->next);
            q->size --;
        }

        if(q->size ==1){
            free(q->head);
            q->size --;
        }
        
    }
    free(q);

}


void enqueue(queue_t q, void *data){

    Node* n = (Node*)malloc(sizeof(Node));

    if(q->size < q->max_size){

        n->data = data;

        if(q->size != 0){
            n->next = q->tail;
            q->tail->prev = n;
            q->tail = n; 
        }

        else{
            q->head = n;
            q->tail = n;
            n->prev = NULL;
            n->next = NULL;
        }

        q->size ++;
        }

}

void *dequeue(queue_t q){

    Node* temp = q->head;
    void *data = temp->data;

    if (q->size > 1) {
        q->head = q->head->prev;
        q->head->next = NULL;
    } 
    
    else {
        q->head = NULL;
        q->tail = NULL;
    }

    free(temp);
    q->size--;
    return data;
}

    

void queue_shutdown(queue_t q){
    q->sd = true;
}



bool is_empty(queue_t q){
    if(q->size > 0){
        return false;
    }
    else{
        return true;
    }
}

bool is_shutdown(queue_t q){
    if((q)->sd == true){
        return true;
    }
    else{
        return false;
    }
}