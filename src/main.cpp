#include <iostream>
#include "Queue.hpp"

int main()
{
  int num{0};

  Queue<int> queue;

  queue.push(1);
  queue.push(2);
  queue.push(3);

  while(!queue.empty()){
    queue.pop(num);
    std::cout << "The Num: " << num << std::endl;
  }; 

  return 0;
}