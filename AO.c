#include "AO.h"

void* activate(active_object*);
active_object* newAO(queue* args_queue, void*, void*);
void destroyAO(active_object* active_);


void* activate(active_object* active_){
    /**
     * @brief this method is the activation method. 
     * argument -> first_func(argument) -> second_func(first_func(argument)).
     * it will run as a thread as long as the active object is active.
     */
    void* front_arg;
    void* first_output;
    void* second_output;

    // run as long as the active_object is active
    while (active_->is_active == 1)
    {
        // pipline
        front_arg = deQ(active_->args_queue);
        first_output = active_->first_func(front_arg);
        second_output = active_->second_func(first_output);
    }
}

active_object* newAO(queue* args_queue, void* _first, void* _second){
    /**
     * @brief this method init a new active object.
     * args_queue is a Queue object that holds the arguments for the first function in it.
     * _first is a pointer to the first function.
     * _second is a pointer to the second function. 
     * it return a new active_object pointer.
     */

    // allocate memory to the new active object
    active_object* _active = (active_object*)malloc(sizeof(active_object));
    // initialize the active_object attributes
    _active->args_queue = args_queue;
    _active->first_func = _first;
    _active->second_func = _second;
    _active->is_active = 1;  // set to alive
    _active->_id = (pthread_t)malloc(sizeof(pthread_t));

    // create a thread for the active object pipline
    pthread_create(_active->_id, NULL, activate, (void*)_active);
    return _active;

}

void destroyAO(active_object* active_){
    /**
     * @brief this method release the resources of the active_object instance.
     * actually destroy the active object.
     */
    active_->is_active = 0;
    free(active_->_id);     // also free the pthread_t attribute
    free(active_);
}
