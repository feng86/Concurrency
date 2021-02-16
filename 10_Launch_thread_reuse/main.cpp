#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

int main()
{

    std::cout << "Main thread id:" << std::this_thread::get_id() << std::endl;
    std::vector<std::future<void>> futures; //a vector of futures whose value type is std::thread::id
    for (int i = 0; i < 10; ++i)
    {
        // std::async returen a future,and future has no copy ctor, have to std::move(fut)...
        //  likewise,emplace_back in vector accept a rvalue reference,value from function return is rvalue?
        //  can: auto fut = std::async(...); v.push_back(std::move(fut));...
        auto fut = std::async(std::launch::deferred, []
    	{
          std::this_thread::sleep_for(std::chrono::seconds(1));
	  // current thread
          auto id = std::this_thread::get_id();
          std::cout << "child thread id:" << std::this_thread::get_id() << std::endl;
    	});
        futures.push_back(std::move(fut));
    }
    std::for_each(futures.begin(),futures.end(),[](std::future<void> &fut)
    {
	fut.wait();
    });     
 
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
/*
when 'auto fut = std::async([]':
Main thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816
child thread id:140699467818816

when 'auto fut = std::async(std::launch::async, []':
Main thread id:140232066369344
child thread id:140232049075968
child thread id:140232040683264
child thread id:140232023897856
child thread id:140232015505152
child thread id:140232032290560
child thread id:140232007112448
child thread id:140231998719744
child thread id:child thread id:140231990327040140231981934336
child thread id:140231973541632

--> both has NO thread stealing at all !
 
when 'auto fut = std::async(std::launch::deferred, []':
Main thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
child thread id:140166630594368
*/
