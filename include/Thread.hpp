#pragma once
#include "Global.hpp"
#include "HangDetector.hpp"
#include "Logger.hpp"

namespace Core{
    class Thread
    {
    private:
        std::once_flag startFlag;
        std::thread m_thread;
        virtual void Work() = 0;
        void ThreadDef();
    public:
        void Start();
        Thread();
        ~Thread();
    };
};