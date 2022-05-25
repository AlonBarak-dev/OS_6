#include <stdio.h>
#include <stdlib.h>

// used the website : https://www.geeksforgeeks.org/queue-linked-list-implementation/ for help in the Queue implementation.


typedef struct Qnode{
    void* key;
    struct Qnode * next;
} node, *pnode;

typedef struct Queue{
    pnode front;
    pnode rear;
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
    
    pnode q_node = createNode(new_node);    // create a new node
    // in case the queue is empty
    if (q_head->front == q_head->rear)
    {
        q_head->front = q_head->rear = q_node;
        return;
    }

    // update the rear to be the new node
    q_head->rear->next = q_node;
    q_head->rear = q_node;
}

void* deQ(queue* q_head){
    /**
     * @brief this method DeQueue an element (void*) 
     * from the Queue and return its value.
     */

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
    // return the value of head.
    return value;
}

void destroyQ(queue* q_head){
    /**
     * @brief this method destroy the entire Queue.
     * it free each of its elements
     * and eventually, it frees the Queue itself.
     */

    // DeQueue each element in the Queue
    while (q_head->front != NULL)
    {
        deQ(q_head);
    }
    // finally, free the Queue itself
    free(q_head);
}