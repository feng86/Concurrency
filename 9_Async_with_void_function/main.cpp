//#include <thread>
#include <future>
#include <iostream>
#include <string>

void fun()
{
    std::cout << "Starting task.\n";
    std::this_thread::sleep_for(std::chrono::seconds(8));
    std::cout << "Ending task.\n";
}

int main()
{
    auto fut = std::async(fun); 
    std::cout << "Exiting from Main.\n";

    return 0;
}
