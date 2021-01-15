#include <thread>
#include <iostream>
#include <vector>

#include <pthread.h>
#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::thread> spawn()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 16; ++i)
    {
        // std::thread itself halts,but it refers to a local variable 'i'
        //  when spawn() returns 'i' disappears
        //  caution for 'pass by reference to local variable' for std::thread
        threads.emplace_back([&]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));
            std::cout << "Hello from thread " << i << "!\n";
        });
    }
    // i's lifetime is shorter than thread function which refers to it.
    //  may fix: move join() here to halt in here to extend i's lifetime which is longer than thread function
    //   but not always practically
    return threads;
}

int main()
{
    std::vector<std::thread> threads;
#if 1
    for (int i = 0; i < 16; ++i)
    {
	// big problem: all 16 threads refer to same variable i here(data structure e.g list) ==> shared memory
        //  different thread runtime scheduling makes different thread sees different transient variable value(i) 
        threads.emplace_back([&]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));
            std::cout << "Hello from thread " << i << "!\n";
        });
    }
#else
    threads = spawn();
#endif
    std::cout << "Hello from main!\n";
    for (auto & t : threads)
        t.join();

    return 0;
 }
