#include <thread>
#include <iostream>
#include <vector>
#include <algorithm> //for_each algorithm

int main()
{
    std::vector<std::thread> threads;//named workers instead of threads
    for (int i = 0; i < 16; ++i)
    {
        // /usr/include/c++/5/bits/vector.tcc
        // template<typename _Tp, typename _Alloc>  
        // template<class.. Args> 
        // void vector<_Tp, _Alloc>::emplace_back (Args&&.. args) //accept a rvalue 
        //  
        //  labmda is temp rvalue and pass to emplace_back,
        threads.emplace_back([i]()
        {
            std::cout << "Hello from thread " << i << "!\n";
        });
    }
    std::cout << "Hello from main!\n";
    for (auto & t: threads)
        t.join();

    auto myId = std::this_thread::get_id();
    std::cout << "Waiting in main thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "/*----------------------------------------*/" << std::endl;

    // push_back has no copy overhead in c++11
    std::vector<std::thread> workers;
    for (int i = 0; i < 16; ++i)
    {
        // /usr/include/c++/5/bits/stl_vector.h
        // push_back(value_type&& __x){ emplace_back(std::move(__x)); } //rvalue as well in c++11
        //  temp std::thread object as its argument
        workers.push_back(std::thread([i]()
        {
            std::cout << "Hello from thread " << i << "!\n";
        }));
    }
    std::cout << "Hello from main!\n";
    // /usr/include/c++/5/bits/stl_algo.h
    // www.cplusplus.com/reference/algorithm/for_each 
    // template<typename _InputIterator, typename _Function>
    // _Function for_each(_InputIterator __first, _InputIterator __last, _Function __f)
    //  Applies function __f/fn to each of the elements in the range [__first,__last).
    //   each element is passed as argument to __f/fn,so refer when ele is changed in __/fn
    std::for_each(workers.begin(),workers.end(),[](std::thread &th){
      th.join();
    });

    return 0;
}
