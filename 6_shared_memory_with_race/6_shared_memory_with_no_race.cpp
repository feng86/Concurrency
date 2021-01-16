#include <cmath>
#include <list>
#include <algorithm>
#include <thread>
#include <iostream>
#include <chrono>

void toSin(std::list<double>& list){
  //  sleep ,make thread main/A's second access shard_memory ahead of thread B
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  // 4. access shared_memory(list) in thrad B
  std::for_each(list.begin(),list.end(),[](double &x)
  {
    x = sin(x);
  });
}

int main(){
  // 1.define shared_memory
  std::list<double> list;
  // 2.access list from main thread A
  const double pi = 3.1415926;
  const double epsilon = 0.0000001;
  for(double x = 0.0; x < 2 * pi + epsilon; x += pi/16) 
    list.push_back(x);
  // 3.start thread B
  //                   through reference: std::ref,parameter for toSin is reference too
  std::thread th(toSin,std::ref(list));

  // 6. access list from mian thread A
  std::for_each(list.begin(),list.end(),[](double &x)
  {
    int count = static_cast<int>(10 * x + 10.5);
    for(int i = 0; i < count; ++i)
      std::cout.put('*');
    std::cout << std::endl;
  });
  
  // 5.join thread():
  th.join();
  
}

// part 3: move 6. ahead of 5.
// thread B creation(in thread main/A) --> thread B starts --(thread B access/write(through reference) shared memory)--> thread B ends --> thread A access/write(through reference) same memory --> thread B join(synchronization point)
