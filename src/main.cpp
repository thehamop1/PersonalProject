#include <iostream>
#include "Core.hpp"

class HelloWorld : public Core::Thread{
  void Work() override{
    LOG(Core::LOGGING_LEVEL::INFO) << "Hello World";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };
};


int main()
{
  std::array<HelloWorld, 4> threads{};
  for(auto& thread : threads){
    thread.Start();
  };

  std::this_thread::sleep_for(std::chrono::seconds(10));
  G_SHUTDOWN=true;
  std::this_thread::sleep_for(std::chrono::seconds(10));
};