#include <thread>
#include <future>
#include <iostream>
#include <string>

// use a normal function not a thread creation + thread function + promise/future + join !!!
//  function returns(type) instead of passed element(type): same DataType
// so no std::thread/join any more
std::string fun(bool flag)
{
    if (flag)
    {
        std::cout << "Worker returning.\n";
        return "Message from worker.";                      // return a std::string matching function return type
    }
    else
    {
        std::cout << "Worker throwing.\n";
        // throw std::exception("Exception from thread.");
        throw std::exception(/*"Exception from thread."*/); // std::exception is not std::string type ???
    }
    return "";
}

int main()
{
    // std::future<std::string> fut = std::async(fun, true);
    // std::async(launch::async/launch::deferred,&callable_object,args) //system choose prefered async or deferred when none is specified. callable_object: normal func/func pointer/lambda/functor
    auto  fut = std::async(fun, false); //so no future/std::thread/join is bothered,but it's just syntax sugar
    std::cout << "Main receiving.\n";
    try
    {
        std::string s = fut.get();
        std::cout << s << std::endl;
    }
    catch (std::exception e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}
