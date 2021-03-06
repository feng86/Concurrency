#include <thread>
#include <future>
#include <iostream>

struct Counter
{
    Counter(int k) : n(k) {}
    int n;
}; 

struct Holder
{
    Holder(int n) 
        : c(new Counter(n)) {}
    Counter * c;
};

int main()
{
    const Holder h(10);
    // this callable_object[lambda here] has no return ,so std::future<void> ?
    std::future<void> fut = std::async([](Holder const & h)
    {
        ++(h.c->n); // h is const ,but modify h 
    }, std::ref(h));
    std::cout << h.c->n << std::endl;
    fut.wait();  // ?
    std::cout << h.c->n << std::endl;
 
    return 0;
}
