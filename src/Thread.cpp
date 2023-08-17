#include "Thread.hpp"
namespace Core{
    Thread::Thread()
    {
    }

    void Thread::Start(){
        std::call_once(startFlag, [&](){
            m_thread = std::thread([&](){
                ThreadDef();
            });
        });
        Core::HangDetector::Instance().AddThread(m_thread.get_id());
    };

    Thread::~Thread()
    {
        m_thread.join();
    }

    void Thread::ThreadDef(){
        while(!G_SHUTDOWN){
            Work();  
            Core::HangDetector::Instance().UpdateEntry(m_thread.get_id());
        }
    };
};