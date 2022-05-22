#include "singleton.hpp"
#include <pthread.h>

using namespace std;

Singleton *Singleton::_instance = 0;
mutex Singleton::_lock;

Singleton* Singleton::instance(){   
    if (_instance == NULL)
    {
        Singleton::_lock.lock();
        if (_instance == NULL)
        {
            _instance = new Singleton{};
        }
        Singleton::_lock.unlock();          
    }
    return _instance;
}



void Singleton::destory(){
    if (this->_instance != NULL)
    {
        this->_lock.lock();
        if (this->_instance != NULL)
        {
            delete this->_instance;
        }
        this->_lock.unlock();
    }
}

void * handle_singleton(void* args){

    Singleton * s = Singleton::instance();
    printf("Thread ID: %d \n", *(int*)args);
    return NULL;
}





int main(){

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    int id_1 = 1;
    int id_2 = 2;
    int id_3 = 3;

    pthread_create(&thread1, NULL, handle_singleton, (void*)&id_1);
    pthread_create(&thread2, NULL, handle_singleton, (void*)&id_2);
    pthread_create(&thread2, NULL, handle_singleton, (void*)&id_3);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}

