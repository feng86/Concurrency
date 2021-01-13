#include <thread>
#include <iostream>

int main()
{
    // define inline anonymous function on the spot
    //  lambda is more intuitive than global function for std::thread object 
    //   just do it in parallel !
    //   differnece between thread-based programming and  task-based programming 
    std::thread t([]()
    {
        std::cout << "Hello from thread!\n";
    });
    std::cout << "Hello from main!\n";
    t.join();
 
    return 0;
}
