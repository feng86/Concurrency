#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <vector>
#include <set>

// Thread pools: work-stealing queue,that "thread(id) reuse"
int main()
{
    std::set<std::thread::id> set;

    std::vector<std::future<std::thread::id>> futures; //a vector of futures whose value type is std::thread::id
    for (int i = 0; i < 30; ++i)
        // std::async returen a future,and future has no copy ctor, have to std::move(fut)...
        //  likewise,emplace_back in vector accept a rvalue reference,value from function return is rvalue?
        //  can: auto fut = std::async(...); v.push_back(std::move(fut));...
        futures.emplace_back(std::async(std::launch::async, []
    {
	// current thread
        auto id = std::this_thread::get_id();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return id; //return each thread's thread_id
    }));
    auto myId = std::this_thread::get_id();
    std::cout << "Waiting in thread " << std::this_thread::get_id() << std::endl;
    for (auto & fut : futures)
    {
        auto id = fut.get(); //get each thread's thread_id
        std::cout << id << "fut.get()\n";
        if (id == myId)
            std::cout << "Parent thread reuse\n";
        if (set.find(id) != set.cend()) // found
            std::cout << "Thread reuse " << id << std::endl;
        set.insert(id);
    }     
 
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
