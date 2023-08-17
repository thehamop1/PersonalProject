#pragma once
#include "Global.hpp"
#include "HangDetector.hpp"

namespace Core{
    class Thread
    {
    private:
        std::thread m_thread;
    public:
        virtual void Work() = 0;
        void ThreadDef();
        Thread();
        ~Thread();
    };
};