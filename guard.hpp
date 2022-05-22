#pragma once
#include <mutex>

template <class T>
class Guard{

    public:
        T* _lock;

        Guard(T*  lock) : _lock(lock){
            lock->lock();
        }

        ~Guard(){
            _lock->unlock();
        }

};