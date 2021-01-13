#include <thread>
#include <iostream>

void threadFun()
{
    std::cout << "Hello from thread!\n";
}

int main()
{
    // std::thread object takes a 
    // callable object[function,lambda,functor,bind] and its arguments 
    // as thread object's arguments
    // https://en.cppreference.com/w/cpp/thread/thread
    std::thread t(threadFun);  
    std::cout << "Hello from main!\n";
    t.join();

    return 0;
}
