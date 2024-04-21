#include <iostream>
#include "Core.hpp"

int main()
{

  Core::LOG(Core::LOGGING_LEVEL::WARNING) << "TEST";

  //Shut down the system
  std::this_thread::sleep_for(std::chrono::seconds(1));
  G_SHUTDOWN=true;
  std::this_thread::sleep_for(std::chrono::seconds(2));
};