#include <iostream>
#include "Core.hpp"

// class HelloWorld : public Core::Thread{
//   private:
//   void Work() override{
//     LOG(Core::LOGGING_LEVEL::INFO) << "Hello World";
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//   };
//   public:
//   ~HelloWorld(){
//     Join();
//   }
// };

using TestPool = Core::Singleton<Core::Internal::MemoryPool<int, 2>>;

int main()
{
  auto frame{TestPool::Instance().Alloc()};
  // std::array<HelloWorld, 4> threads{};
  // for(auto& thread : threads){
  //   thread.Start();
  // };
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  // G_SHUTDOWN=true;
  // std::this_thread::sleep_for(std::chrono::seconds(10));

    

};