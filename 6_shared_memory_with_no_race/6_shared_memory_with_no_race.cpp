#include<cmath>
#include<list>
#include <algorithm>
#include <thread>
#include <iostream>
void toSin(std::list<double>& list){
  std::for_each(list.begin(),list.end(),[](double &x)
  {
    x = sin(x);
  });
}

int main(){
  std::list<double> list;
  // access list from main thread A
  const double pi = 3.1415926;
  const double epsilon = 0.0000001;
  for(double x = 0.0; x < 2 * pi + epsilon; x += pi/16) 
    list.push_back(x);
  // start thread B
  //                   through reference: std::ref,parameter for toSin is reference too
  std::thread th(toSin,std::ref(list));
  
  // join thread():
  th.join();
  
  // access list from mian thread A
  std::for_each(list.begin(),list.end(),[](double &x)
  {
    int count = static_cast<int>(10 * x + 10.5);
    for(int i = 0; i < count; ++i)
      std::cout.put('*');
    std::cout << std::endl;
  });
}

// part 3
// thread B creation(in thread main/A) --> thread B starts --(thread B access/write(through reference) shared memory)--> thread B ends --> thread B join(synchronization point) --> thread A access/write(through reference) same memory.
