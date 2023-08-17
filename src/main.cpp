#include <iostream>
#include "Core.hpp"

class HelloWorld : private Core::Thread{
  void Work() override{
    LOG(Core::LOGGING_LEVEL::INFO) << "Hello World";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };
};


int main()
{
  Core::HangDetector::Instance();
};