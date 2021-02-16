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
	// bad thing: a exception is generated and throwed!!!
        throw std::bad_exception(/*"Exception from thread."*/); // 1. throw exception in promise thread. 0 arguments
    }
    catch (...)//all possible exception
    {   // catch and pass exception to future thread!!!
        pr.set_exception(std::current_exception()); // 2. use "..." to catch exception,so no reference to catched exception,so use "std::current_exception()"
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
        std::string s = fut.get(); // 3. exception is rethrown when call fut.get() !!!
        std::cout << s << std::endl;
    } // set_exception in promise thread. and catch again in future thread!!!
    catch (std::exception& e) // 4. recatch what we know (is a exception) in future thread !
    {
        std::cout << "Caught: " << e.what() << std::endl;//Caught: std::bad_exception or Caught: std::exception
    }
    th.join();
 
    return 0;
}
