#pragma once
#include "Singleton.hpp"

#include <queue>
#include <atomic>
#include <sstream>
#include <mutex>
#include <iostream>


namespace Core{
    enum class LOGGING_LEVEL{
        VERBOSE,
        INFO,
        WARNING,
        ERROR,
    };

    namespace Internal{
        class LoggingSystem
        {
        private:
            std::atomic<bool> m_enabled=true;
            std::mutex m_queueLock;
            std::queue<std::string> m_loggingStatements;
        public:
            bool QueueLog(const std::string&& log);
            LoggingSystem();
            ~LoggingSystem();
        };
        using Logger = Core::Singleton<Core::Internal::LoggingSystem>;

        class LogBuilder{
            private:
                LOGGING_LEVEL m_logLevel=LOGGING_LEVEL::VERBOSE;
                std::stringstream m_logLine;
            public:
                LogBuilder(const LOGGING_LEVEL& LogLevel);
                ~LogBuilder();

                template<typename T>
                LogBuilder& operator<<(const T& data){
                    m_logLine << data;
                    return *this;
                };
        };
    };

    static Internal::LogBuilder LOG(const LOGGING_LEVEL& LogLevel, std::string_view log){
        Internal::Logger::Instance().QueueLog(log);
    }
    static Internal::LogBuilder LOG(const LOGGING_LEVEL& LogLevel){
        return Internal::LogBuilder(LogLevel);
    };
};
