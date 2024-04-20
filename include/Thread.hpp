#pragma once
#include "Global.hpp"
#include "HangDetector.hpp"
#include "Logger.hpp"

namespace Core{
    class Thread
    {
    private:
        std::once_flag m_startFlag;
        std::thread m_thread;
        virtual void Work() = 0;
        void ThreadDef();
     
    public:
        void Join();
        void Start();
        Thread();
        virtual ~Thread()=default;
    };
};