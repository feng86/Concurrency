#include <thread>
#include <iostream>
#include <string>

void repeat(std::string & str, int n)
{
    if (n > 0)
    {
        str[0] = 'B';
        std::cout << str;
        repeat(str, n - 1);
    }
}

int main()
{
    //    std::thread t(repeat, "blah!", 3);
    std::string str("blah!");
    // copy semantics: pointer data memeber,class needs 'deep copy' for copy ctor/assignment operator
    // move semantics: when source(rvalue) is no longer used any more,
    //  1) 'no deep copy! just switch/move pointer in copy ctor/assignment operator when source is rvalue'. 
    //       need to introduce rvalue reference!
    //       mulitple objects(e.g std::thread) refers to same object-->alias,not good for std::thread 
    //  2)  since std::thread is 'variadic template parameter',str is string so ctor for std::thread is deduced to string
    //       while first parameter of repeat is reference,so a temp var for str is refered that is not what we want.==> std::ref(xxx) to rescue
    //      remember: use std::ref(xxx) when 'thread fucntion' parameter is reference 
    std::thread t(repeat, std::ref(str), 3);
    std::cout << "[Hello from main!]";
    t.join();
    std::cout << std::endl << str;
 
    return 0;
}
