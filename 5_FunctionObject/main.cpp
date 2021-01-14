#include <thread>
#include <iostream>
#include <vector>

class FunObj
{
public:
    FunObj(int i) : _i(i)
    {}
    void operator()(int j)
    {
        std::cout << "Hello from thread " << _i << "--" << j << " !\n";
    }
private:
    int _i;
};

int main()
{
    // run a functor in a std::thread
    //  functor can wrap data in a class/struct type
    //  arguments can be passed in functor,no need for std::thread
    //  no arguments at all if '2' is part of class/struct and passed in ctor
    std::vector<std::thread> threads;
    for (int i = 0; i < 16; ++i)
    {
        threads.emplace_back(FunObj(i),2);
    }
    std::cout << "Hello from main!\n";
    for (auto & t: threads)
        t.join();
  
    return 0;
}
