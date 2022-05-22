#include "guard.hpp"
#include <pthread.h>

using namespace std;

mutex global_lock;


void* print_id(void* args){

    Guard<mutex> g_lock{&global_lock};

    for (size_t i = 0; i < 50; i++)
    {
        printf("Thread ID: %d \n", *(int*)args);
    }
    return NULL;
}

int main(){

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    int id_1 = 1;
    int id_2 = 2;
    int id_3 = 3;

    pthread_create(&thread1, NULL, print_id, (void*)&id_1);
    pthread_create(&thread2, NULL, print_id, (void*)&id_2);
    pthread_create(&thread2, NULL, print_id, (void*)&id_3);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);


    return 0;

}