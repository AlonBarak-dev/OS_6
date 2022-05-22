#pragma once 
#include <mutex>
#include <iostream>

class Singleton{

    static std::mutex _lock;
    static Singleton * _instance;


    private:
        Singleton(){
            
            std::cout << "Constructor is running" << std::endl;
        }
        ~Singleton(){
            std::cout << "Destructor is running" << std::endl;
        }    


    public:

        static Singleton* instance();
        void destory();
};