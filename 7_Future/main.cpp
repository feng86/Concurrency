#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <memory>

/*
  You can think of thread as simpled synchronizied function which can 
   accept some arguments and may return some 'value'(still return 'void' for thread function)

  Use promise(input/sending side)/future(future object is get(get_future) from future object(so,promise/future can    be 1-1 map); output/recevie side) communicaiton channel for returning 'value' between 2 threads 

  Promise/Future is template class,can transfer any type of one object 

  When a Promise object is defined, a 'shared state' is allocated  automatically ,this is state which 'value ' is stored; When a Future object is obtained form a Promise object form pr.get_future() ,at this state,'shared state' is shared by both Promise/Future object. it has a ref-count, when promise/future objects go out of scope ,this 'shared state' will be  reclaimed.
 
  Promise/future can also be used in 'one thread',since it can not only pass value but exception!

  When you defined your new thread object(current thread is 'main thread'; and pass the promise or future to new thread). Now thread owning promise object is input/sending side,thread owning future object is output/receiving side,and 'shared state' is refered by this two threads,ref-count==2,and "synchronization is provided by system"!!!. Now,promise thread: pr.set_value(T),and future thread: fut.get(),
  when fut.get() before the pr.set_value(T),then it will be blocked("synchronization") and "wait till the pr.set_value(T)". Internally, "shared_state stores the value and is set form empty to ready,and signal the future thread to grab the value and change the shared_state to invalid state because fut.get() can get/copy the value or std::move() the value. call fut.get() two times will be error when std::move(),since shared_state is changed to invalid state after first time called.

  Why not use regular/normal function just to return value,no promise/future is involved!!! ---std::Async [see 9_Async],but std::Async object accept a funcion[named "task"] as a argument and return a std::future,use fut.get() to get the value returned from function . no thread is involved ,no join() is needed.
  What about exception for std::Async
*/

void fun(std::promise<std::string>&& pr, std::unique_ptr<int> uptr)//rvalue reference since std::move for augument
{
    // 4. put element in channel
    std::cout << (void *)(uptr.get()) << std::endl; //0x196ac20
    std::cout << "Worker sending.\n";
    pr.set_value("Message from thread.");

    /*
     std::string str = "test string";
     std::cout << (void *)(str.data()) << std::endl; //data() return a buffer which points to a char[].raw pointer like 0x196ac20
     pr.set_value(str); // string is passed by move !!!
     ...
     std::string s = fut.get();                      // later in another/main thread
     std::cout << (void *)(str.data()) << std::endl; // later in another/main thread. same raw pointer,so its std::move !!!
     
    */

    /*
     what about a exception is throwed inside a thread? [see 8_Except]
    */
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
    //   must "move promise after get_future from promise",since promise is empty after promise is moved to child thread
    std::thread th(fun, std::move(pr), std::move(uptr));//std::move(pr) or pass the reference[see 7_Future_ref_promise] !
    std::cout << "Main receiving.\n";
    // 5. get element in channel; get by value or by move(elements decrease one or become empty,next get wll be blocked)
    //  here,string is passed by move through promise/future mechanism!!! no copy is done
    std::string s = fut.get();
    std::cout << s << std::endl;
  
    // can join at any point
    // even could join before future get value in which case,get() will return immediately...
    th.join();//main thread waits suthread ending
 
    return 0;
}
// promise/future is template, T is element type that passed through promise/future
// promise public data to channel,singal future to get,or future is blocked when no data is put in promise side.

// pass a string(char * contained in a string) by move in communication channel,so input side and output side can see same char* address !!!
