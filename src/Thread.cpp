#include "Thread.hpp"
namespace Core{
    Thread::Thread()
    {
        Core::HangDetector::Instance().AddThread(m_thread.get_id());
    }

    Thread::~Thread()
    {
    }

    void Thread::ThreadDef(){
        Work();  
        Core::HangDetector::Instance().UpdateEntry(m_thread.get_id());
    };
}