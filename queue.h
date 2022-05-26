#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>    // compile using -lpthread
#include <string.h>

// used the website : https://www.geeksforgeeks.org/queue-linked-list-implementation/ for help in the Queue implementation.


typedef struct Qnode{
    void* key;
    struct Qnode * next;
} node, *pnode;

typedef struct Queue{
    pnode front;
    pnode rear;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} queue;

pnode createNode(void* key);
queue* createQ();
void enQ(queue* q_head, void* new_node);
void* deQ(queue* q_head);
void destroyQ(queue* q_head);
