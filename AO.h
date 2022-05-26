#include "queue.h"

typedef struct active_object_struct{

    queue* args_queue;
    pthread_t _id;
    void* (*first_func)(void*);
    void* (*second_func)(void*);
    int is_active;       // 0 - false, 1 - true

}active_object;

void* activate(active_object*);
active_object* newAO(queue* args_queue, void*, void*);
void destroyAO(active_object* active_);