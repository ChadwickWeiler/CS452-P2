#include "lab.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


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

    pthread_mutex_t m_lock;
    //condition full means q is full
    pthread_cond_t full;
    //means q contains data
    pthread_cond_t data_exists;

} queue;


queue_t queue_init(int capacity){
    
    queue_t new_q = (queue_t)malloc(sizeof(struct queue));
    
        if(new_q == NULL){
            printf("missing data\n");
            free(new_q);
            return NULL;
        }
    
    pthread_mutex_init(&new_q->m_lock, NULL);
    pthread_cond_init(&new_q->full, NULL);
    pthread_cond_init(&new_q->data_exists, NULL);

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

    pthread_mutex_destroy(&q->m_lock);

    pthread_cond_destroy(&q->data_exists);
    pthread_cond_destroy(&q->full);

    free(q);
    
}


void enqueue(queue_t q, void *data){
    
    pthread_mutex_lock(&q->m_lock);

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

            pthread_cond_signal(&q->data_exists);
            pthread_mutex_unlock(&q->m_lock);
        }

    else {
        while(q->size == q->max_size){
            pthread_cond_wait(&q->data_exists, &q->m_lock);
        }
    }
    pthread_mutex_unlock(&q->m_lock);
}

void *dequeue(queue_t q){
    
    pthread_mutex_lock(&q->m_lock);
    
    //if the queue is empty, wait until data has been inserted to execute
    while (q->size == 0) {
        pthread_cond_wait(&q->data_exists, &q->m_lock);
    }

    if(q->size > 0){
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
        pthread_cond_signal(&q->data_exists);
        pthread_mutex_unlock(&q->m_lock);
        return data;
    }
    
    pthread_mutex_unlock(&q->m_lock);
    return NULL;
    
}

    

void queue_shutdown(queue_t q){
    pthread_mutex_lock(&q->m_lock);
    q->sd = true; 
    pthread_mutex_unlock(&q->m_lock);
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