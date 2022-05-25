#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>    // compile using -lpthread

// used the website : https://www.geeksforgeeks.org/queue-linked-list-implementation/ for help in the Queue implementation.


typedef struct Qnode{
    void* key;
    struct Qnode * next;
} node, *pnode;

typedef struct Queue{
    pnode front;
    pnode rear;
    pthread_mutex_t lock;
} queue;

pnode createNode(void* key){
    /**
     * @brief this method creates a new Q node.
     * it initialize it with the given key and set its next to NULL.
     * 
     */
    pnode n = (pnode)malloc(sizeof(node));
    n->key = key;
    n->next = NULL;
    return n;
}

queue* createQ(){
    /**
     * @brief this method creates an empty Queue.
     * it initialize both front and rear to NULL.
     */
    queue* queue_head = (queue*) malloc(sizeof(queue));
    queue_head->front = queue_head->rear = NULL;
    return queue_head;
}

void enQ(queue* q_head, void* new_node){
    /**
     * @brief this method insert a new value (void*) 
     * into the Queue.
     * it allocate memory for the new element
     * using the createNode method.
     */
    pthread_mutex_lock(&q_head->lock);  // lock 
    pnode q_node = createNode(new_node);    // create a new node
    // in case the queue is empty
    if (q_head->front == NULL)
    {
        q_head->front = q_head->rear = q_node;
        pthread_mutex_unlock(&q_head->lock);        // release
        return;
    }

    // update the rear to be the new node
    q_head->rear->next = q_node;
    q_head->rear = q_node;
    pthread_mutex_unlock(&q_head->lock);    // release
}

void* deQ(queue* q_head){
    /**
     * @brief this method DeQueue an element (void*) 
     * from the Queue and return its value.
     */

    pthread_mutex_lock(&q_head->lock);  // lock

    // in case the Queue is empty, return NULL
    if (q_head->front == NULL)
    {
        return NULL;
    }
    // enqueue the front of the queue
    pnode head = q_head->front;
    q_head->front = q_head->front->next;

    // if front is NULL, set rear to be NULL as well
    if (q_head->front == NULL)
    {
        q_head->rear = NULL;
    }
    // extract the value from the head
    void* value = head->key;
    // free the memory of head as its not needed anymore
    free(head);
    pthread_mutex_unlock(&q_head->lock);    // release
    // return the value of head.
    return value;
}

void destroyQ(queue* q_head){
    /**
     * @brief this method destroy the entire Queue.
     * it free each of its elements
     * and eventually, it frees the Queue itself.
     */

    pthread_mutex_lock(&q_head->lock);  // lock

    // DeQueue each element in the Queue
    while (q_head->front != NULL)
    {
        deQ(q_head);
    }
    // finally, free the Queue itself
    free(q_head);
}

int main(){

    // creates a new Queue
    queue* q_head = createQ();
    int * value = (int*)malloc(sizeof(int));
    *value = 10;
    enQ(q_head, value);
    int * value1 = (int*)malloc(sizeof(int));
    *value1 = 22;
    enQ(q_head, value1);
    void* del = deQ(q_head);
    printf("%d\n", *(int*)del);  
    del = deQ(q_head);
    printf("%d\n", *(int*)del); 

    free(value1);
    free(value);

    return 0;
}