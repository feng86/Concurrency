#include <thread>
#include <future>
#include <memory>
#include <iostream>
#include <chrono>

// no value is returned from this normal function
//  you can still call fut.get(),when you call fut.get(), it call the function and it "extract future",but return nothing
void threadFun(std::unique_ptr<int> p)
{
  std::cout << "start task.\n";
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "end task.\n";
}

int main()
{
    std::unique_ptr<int> up(new int(10));
    auto fut = std::async(threadFun, std::move(up));
    fut.get(); //just called,no lhs is involved; it forces function to be called !!!

    return 0;
}
