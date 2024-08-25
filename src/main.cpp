#include "Core.hpp"

using TestPool = Core::Singleton<Core::Internal::MemoryPool<int, 2>>;

int main()
{
  auto frame{TestPool::Instance().Alloc()};
  //auto frame2{TestPool::Instance().Alloc()}; 
  //frame = 2;
  //frame2 = frame;
  //std::cout << "Hello World" << std::endl;
  // std::array<HelloWorld, 4> threads{};
  // for(auto& thread : threads){
  //   thread.Start();
  // };
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  // G_SHUTDOWN=true;
  // std::this_thread::sleep_for(std::chrono::seconds(10));
};
