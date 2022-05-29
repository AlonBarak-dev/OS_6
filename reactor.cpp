#include "reactor.hpp"
#include <stdlib.h>


void Reactor::installHandler(void* (function)(void*), const int* file_desc){
    /**
     * @brief this method insert values into the new Reactor.
     */
    
    this->function = function;
    this->file_desc = *file_desc;
    // create a new thread with the given arguments
    this->p_id = (pthread_t)malloc(sizeof(pthread_t));
    pthread_create(&this->p_id, NULL, this->function, (void*)file_desc);
}

void Reactor::RemoveHandler(){
    /**
     * @brief this method destroy the Reactor and free its allocated attributes.
     */

    this->function = NULL;
    this->file_desc = -1;
    // kill the thread
    pthread_cancel(this->p_id);
    // call the private destructor
    this->~Reactor();
}