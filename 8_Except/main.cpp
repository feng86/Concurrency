#include <thread>
#include <future>
#include <iostream>
#include <string>

void fun(std::promise<std::string> && pr)
{
    try
    {
        std::cout << "Worker throwing.\n";
        // /usr/include/c++/5/exception:63:5: note:   candidate expects 0 arguments, 1 provided
        // throw std::exception(/*"Exception from thread."*/);
        throw std::bad_exception(/*"Exception from thread."*/);
    }
    catch (...)//all possible exception
    {
        pr.set_exception(std::current_exception());
    }
}

int main()
{
    std::promise<std::string> pr;
    std::future<std::string> fut = pr.get_future();
    std::thread th(fun, std::move(pr));
    std::cout << "Main receiving.\n";
    try
    {
        std::string s = fut.get();
        std::cout << s << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Caught: " << e.what() << std::endl;//Caught: std::bad_exception or Caught: std::exception
    }
    th.join();
 
    return 0;
}
