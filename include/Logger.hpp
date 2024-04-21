#pragma once
#include "Singleton.hpp"
#include "Global.hpp"

#include <queue>
#include <atomic>
#include <sstream>
#include <mutex>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <thread>


namespace Core{
    enum class LOGGING_LEVEL{
        VERBOSE=0,
        INFO=1,
        WARNING=2,
        ERROR=3,
    };
    static constexpr std::array<std::string_view, 4> LOGGING_LEVEL_TO_STRING{
        "VERBOSE",
        "INFO",
        "WARNING",
        "ERROR"
    };

    namespace Internal{
        class LoggingSystem
        {
        private:
            std::ofstream m_file;
            std::thread m_loggingThread;
            std::atomic<bool> m_enabled{true};
            std::mutex m_queueLock;
            std::queue<std::string> m_loggingStatements;
            void LoggingThread();
        public:
            std::string FileName();
            void QueueLog(const std::string&& log);
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

    static Internal::LogBuilder LOG(const LOGGING_LEVEL& LogLevel){
        return Internal::LogBuilder(LogLevel);
    };
};
