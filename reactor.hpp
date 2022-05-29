#pragma once
#include <pthread.h>

class Reactor{

    private:
        Reactor(){}
        ~Reactor(){
            free(this->p_id);
            delete this;
        }
    
    public:

        pthread_t p_id;
        void* (*function)(void*);
        int file_desc;

        friend void* newReactor();
        void installHandler(void *(function)(void*),const int*);
        void RemoveHandler();

};