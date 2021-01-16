#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <memory>

void fun(std::promise<std::string>&& pr, std::unique_ptr<int> uptr)
{
    // 4. put element in channel
    std::cout << (void *)(uptr.get()) << std::endl; //0x196ac20
    std::cout << "Worker sending.\n";
    pr.set_value("Message from thread.");
}

int main()
{
    // create data through smart-pointer
    std::unique_ptr<int> uptr(new int(10));
  
    // 1. parent thread create promise
    std::promise<std::string> pr;
    std::cout << (void *)(uptr.get()) << std::endl; //0x196ac20
    // 2. get future from this promise 
    std::future<std::string> fut = pr.get_future();
    // 3. 
    // input side owns the promise; output side owns the future
    //  so ,parent thread decides which promise or future is passed to child thread
    //  here,child thread return value to parent thread ,child thread acts a input-side;owns the promise
    //   must move promise after get_future from promise,since promise is empty after promise is moved to child thread
    std::thread th(fun, std::move(pr), std::move(uptr));
    std::cout << "Main receiving.\n";
    // 5. get element in channel; get by value or by move(elements decrease one or become empty,next get wll be blocked)
    //  here,string is passed by move through promise/future mechanism!!! no copy is done
    std::string s = fut.get();
    std::cout << s << std::endl;
  
    // even could join before future get value ...
    th.join();
 
    return 0;
}
// promise/future is template, T is element type that passed through promise/future
// promise public data to channel,singal future to get,or future is blocked when on data is put in promise side.

// pass a string(char * contained in a string) by move in communication channel,so input side and output side can see same char* address !!!
