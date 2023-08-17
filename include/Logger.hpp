#pragma once
#include "Singleton.hpp"

#include <queue>
#include <atomic>

enum class LOGGING_LEVEL{
    VERBOSE,
    INFO,
    WARNING,
    ERROR,
};

class LOG{

};

namespace Core{
    namespace Internal{
        class Logger
        {
        private:
            std::atomic<bool> m_enabled=true;

        public:
            Logger();
            ~Logger();
        };
    };
};

using Logger = Core::Singleton<Core::Internal::Logger>;